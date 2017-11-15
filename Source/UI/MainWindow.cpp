#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Options.h"
#include "Cave.h"
#include "Core/Defines.h"
#include "Core/Settings.h"
#include <QtWidgets>

MainWindow::MainWindow() :
        _ui(new Ui::MainWindow) {
    _ui->setupUi(this);

    _treeView = new QTreeView;
    _treeView->setFrameShape(QFrame::NoFrame);
    _treeView->setHeaderHidden(true);
    QFileSystemModel* fsModel = new QFileSystemModel;
    _treeView->setModel(fsModel);
    QString workspaceDir = Settings::instance()->readWorkspace();
    QDir dir;
    dir.mkpath(workspaceDir);
    QModelIndex index = fsModel->setRootPath(workspaceDir);
    _treeView->setRootIndex(index);
    for (int i = 1; i < fsModel->columnCount(); ++i) {
        _treeView->hideColumn(i);
    }

    _ui->tabWidgetSideBar->addTab(_treeView, tr("Workspace"));
    _ui->tabWidgetSideBar->addTab(new QWidget, tr("Properties"));

    readSettings();
}

MainWindow::~MainWindow() {
    delete _ui;
}

void MainWindow::on_actionNew_triggered() {
    QString workspaceDir = Settings::instance()->readWorkspace();
    QString filePath = QFileDialog::getSaveFileName(this, tr("Create Irbis File"), workspaceDir, "Irbis (*.irbis);;All Files(*.*)");
    if (!filePath.isEmpty()) {
        QFileInfo info(filePath);
        if (info.suffix() != "irbis") {
            filePath += ".irbis";
        }
        changeWindowTitle(filePath);
        QFileInfo fi(filePath);
        int index = _ui->tabWidgetCave->addTab(new Cave(filePath), fi.fileName());
        _ui->tabWidgetCave->setTabToolTip(index, filePath);
        _ui->tabWidgetCave->setCurrentIndex(index);
    }
}

void MainWindow::on_actionOpen_triggered() {
    QString workspaceDir = Settings::instance()->readWorkspace();
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open Irbis File"), workspaceDir, "Irbis (*.irbis);;All Files(*.*)");
    if (!filePath.isEmpty()) {
        changeWindowTitle(filePath);
        QFileInfo fi(filePath);
        int index = _ui->tabWidgetCave->addTab(new Cave(filePath), fi.fileName());
        _ui->tabWidgetCave->setCurrentIndex(index);
    }
}

void MainWindow::on_actionSaveAs_triggered() {
    QString workspaceDir = Settings::instance()->readWorkspace();
    QString filePath = QFileDialog::getSaveFileName(this, tr("Save Irbis File"), workspaceDir, "Irbis (*.irbis);;All Files(*.*)");
    if (!filePath.isEmpty()) {
        QFileInfo info(filePath);
        if (info.suffix() != "irbis") {
            filePath += ".irbis";
        }
        changeWindowTitle(filePath);
        QFileInfo fi(filePath);
        int index = _ui->tabWidgetCave->addTab(new Cave(filePath), fi.fileName());
        _ui->tabWidgetCave->setCurrentIndex(index);
    }
}

void MainWindow::on_actionClose_triggered() {
//    _cave->closeIrbis();
    changeWindowTitle();
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

void MainWindow::readSettings() {
    Settings::instance()->beginGroup("MainWindow");

    resize(Settings::instance()->value("size", QSize(1000, 600)).toSize());
    move(Settings::instance()->value("pos", QPoint(200, 200)).toPoint());

    QVariant splitterSize = Settings::instance()->value("splitter");
    if (splitterSize == QVariant()) {
        _ui->splitter->setSizes({ 100, 500 });
    } else {
        _ui->splitter->restoreState(splitterSize.toByteArray());
    }

    _ui->actionShowSidebar->setChecked(Settings::instance()->value("showSidebar", true).toBool());

    Settings::instance()->endGroup();

    Settings::instance()->beginGroup("Cave");
//    QString filePath = Settings::instance()->value("filePath").toString();
//    if (!filePath.isEmpty()) {
//        changeWindowTitle(filePath);
//        QFileInfo fi(filePath);
//        int index = _ui->tabWidgetCave->addTab(new Cave(filePath), fi.fileName());
//        _ui->tabWidgetCave->setCurrentIndex(index);
//    } else {
//        changeWindowTitle();
//    }
    Settings::instance()->endGroup();
}

void MainWindow::writeSettings() {
    Settings::instance()->beginGroup("MainWindow");
    Settings::instance()->setValue("size", size());
    Settings::instance()->setValue("pos", pos());
    Settings::instance()->setValue("splitter", _ui->splitter->saveState());
    Settings::instance()->setValue("showSidebar", _ui->actionShowSidebar->isChecked());
    Settings::instance()->endGroup();

    Settings::instance()->beginGroup("Cave");
//    Settings::instance()->setValue("filePath", _cave->filePath());
    Settings::instance()->endGroup();
}

void MainWindow::changeWindowTitle(const QString& filePath) {
    QString title = QApplication::applicationName();
    if (!filePath.isEmpty()) {
        QFileInfo info(filePath);
        title += " - " + info.fileName();
    }
    setWindowTitle(title);
}

void MainWindow::closeEvent(QCloseEvent* event) {
    writeSettings();
    event->accept();
}
