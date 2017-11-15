#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Options.h"
#include "Cave.h"
#include "Core/Defines.h"
#include "Core/Settings.h"
#include <QtWidgets>

MainWindow::MainWindow() :
        _ui(new Ui::MainWindow) {
    _settings = Settings::instance();

    _ui->setupUi(this);

    _treeView = new QTreeView;
    _treeView->setFrameShape(QFrame::NoFrame);
    _treeView->setHeaderHidden(true);
    _fsModel = new QFileSystemModel;
    _treeView->setModel(_fsModel);
    QString workspaceDir = _settings->readWorkspace();
    QDir dir;
    dir.mkpath(workspaceDir);
    QModelIndex index = _fsModel->setRootPath(workspaceDir);
    _treeView->setRootIndex(index);
    for (int i = 1; i < _fsModel->columnCount(); ++i) {
        _treeView->hideColumn(i);
    }

    connect(_treeView, &QTreeView::doubleClicked, this, &MainWindow::onFileDoubleClicked);

    _ui->tabWidgetSideBar->addTab(_treeView, tr("Workspace"));
    _ui->tabWidgetSideBar->addTab(new QWidget, tr("Properties"));

    readSettings();
}

MainWindow::~MainWindow() {
    delete _ui;
}

void MainWindow::on_actionNew_triggered() {
    QString workspaceDir = _settings->readWorkspace();
    QString filePath = QFileDialog::getSaveFileName(this, tr("Create Irbis File"), workspaceDir, "Irbis (*.irbis);;All Files(*.*)");
    if (!filePath.isEmpty()) {
        addCaveTab(filePath);
    }
}

void MainWindow::on_actionOpen_triggered() {
    QString workspaceDir = _settings->readWorkspace();
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open Irbis File"), workspaceDir, "Irbis (*.irbis);;All Files(*.*)");
    if (!filePath.isEmpty()) {
        addCaveTab(filePath);
    }
}

void MainWindow::on_actionSaveAs_triggered() {
    QString workspaceDir = _settings->readWorkspace();
    QString filePath = QFileDialog::getSaveFileName(this, tr("Save Irbis File"), workspaceDir, "Irbis (*.irbis);;All Files(*.*)");
    if (!filePath.isEmpty()) {
        addCaveTab(filePath);
    }
}

void MainWindow::on_actionClose_triggered() {
    on_tabWidgetCave_tabCloseRequested(_ui->tabWidgetCave->currentIndex());
}

void MainWindow::on_actionCloseAll_triggered() {
    while (_ui->tabWidgetCave->count()) {
        on_tabWidgetCave_tabCloseRequested(0);
    }
}

void MainWindow::on_actionCloseOther_triggered() {
    int i = 0;
    while (_ui->tabWidgetCave->count() > 1) {
        if (i != _ui->tabWidgetCave->currentIndex()) {
            on_tabWidgetCave_tabCloseRequested(i);
        } else {
            i++;
        }
    }
}

void MainWindow::on_actionExit_triggered() {
    QApplication::quit();
}

void MainWindow::on_actionOptions_triggered() {
    Options options(this);
    options.exec();
}

void MainWindow::on_actionShowSidebar_toggled(bool checked) {
    if (checked) {
        _ui->tabWidgetSideBar->show();
    } else {
        _ui->tabWidgetSideBar->hide();
    }
}

void MainWindow::on_actionAbout_triggered() {
    QMessageBox::about(this, tr("About %1").arg(APP_NAME),
        tr("<h3>%1 %2</h3> \
           Based on Qt %3<br> \
           Build on %4<br><br> \
           <a href=%5>%5</a><br><br> \
           Copyright © 2017, Vladimir Zarypov").
           arg(APP_NAME).arg(APP_VERSION_STR).arg(QT_VERSION_STR).arg(__DATE__).arg(APP_URL));
}

void MainWindow::on_tabWidgetCave_tabCloseRequested(int index) {
    QWidget* widget = _ui->tabWidgetCave->widget(index);
    _ui->tabWidgetCave->removeTab(index);
    delete widget;
}

void MainWindow::on_tabWidgetCave_currentChanged(int index) {
    if (index >= 0) {
        QString filePath = static_cast<Cave*>(_ui->tabWidgetCave->widget(index))->filePath();
        QModelIndex modelIndex = _fsModel->index(filePath);
        _treeView->setCurrentIndex(modelIndex);
        changeWindowTitle(filePath);
    } else {
        _treeView->setCurrentIndex(QModelIndex());
        changeWindowTitle();
    }
}

void MainWindow::onFileDoubleClicked(const QModelIndex& index) {
    addCaveTab(_fsModel->filePath(index));
}

void MainWindow::readSettings() {
    _settings->beginGroup("MainWindow");

    resize(_settings->value("size", QSize(1000, 600)).toSize());
    move(_settings->value("pos", QPoint(200, 200)).toPoint());

    QVariant splitterSize = _settings->value("splitter");
    if (splitterSize == QVariant()) {
        _ui->splitter->setSizes({ 100, 500 });
    } else {
        _ui->splitter->restoreState(splitterSize.toByteArray());
    }

    _ui->actionShowSidebar->setChecked(_settings->value("showSidebar", true).toBool());

    _settings->endGroup();

    if (_settings->readRestoreSession()) {
        _settings->beginGroup("Session");
        QStringList keys = _settings->allKeys();
        for (int i = 0; i < keys.count(); i++) {
            QString filePath = _settings->value(keys.at(i)).toString();
            QFileInfo fi(filePath);
            if (fi.exists()) {
                addCaveTab(filePath);
            }
        }
        _settings->endGroup();
    }
}

void MainWindow::writeSettings() {
    _settings->beginGroup("MainWindow");
    _settings->setValue("size", size());
    _settings->setValue("pos", pos());
    _settings->setValue("splitter", _ui->splitter->saveState());
    _settings->setValue("showSidebar", _ui->actionShowSidebar->isChecked());
    _settings->endGroup();

    if (_settings->readRestoreSession()) {
        _settings->remove("Session");
        _settings->beginGroup("Session");
        for (int i = 0; i < _ui->tabWidgetCave->count(); i++) {
            Cave* cave = static_cast<Cave*>(_ui->tabWidgetCave->widget(i));
            _settings->setValue(QString::number(i), cave->filePath());
        }
        _settings->endGroup();
    }
}

void MainWindow::changeWindowTitle(const QString& filePath) {
    QString title = QApplication::applicationName();
    if (!filePath.isEmpty()) {
        QFileInfo info(filePath);
        title += " - " + info.fileName();
    }
    setWindowTitle(title);
}

void MainWindow::addCaveTab(const QString& filePath) {
    QString fullIrbisPath = filePath;
    QFileInfo info(fullIrbisPath);
    if (info.suffix() != "irbis") {
        fullIrbisPath += ".irbis";
    }

    int tabIndex = findCave(fullIrbisPath);
    if (tabIndex != -1) {
        _ui->tabWidgetCave->setCurrentIndex(tabIndex);
    } else {
        QFileInfo fi(fullIrbisPath);
        int index = _ui->tabWidgetCave->addTab(new Cave(fullIrbisPath), fi.fileName());
        _ui->tabWidgetCave->setTabToolTip(index, fullIrbisPath);
        _ui->tabWidgetCave->setCurrentIndex(index);
    }

    changeWindowTitle(fullIrbisPath);
}

int MainWindow::findCave(const QString& filePath) {
    for (int i = 0; i < _ui->tabWidgetCave->count(); i++) {
        Cave* cave = static_cast<Cave*>(_ui->tabWidgetCave->widget(i));
        if (cave->filePath() == filePath) {
            return i;
        }
    }

    return -1;
}

void MainWindow::closeEvent(QCloseEvent* event) {
    writeSettings();
    event->accept();
}
