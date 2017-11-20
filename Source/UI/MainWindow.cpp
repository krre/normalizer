#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Options.h"
#include "NewProject.h"
#include "NewFile.h"
#include "Cave.h"
#include "Core/Defines.h"
#include "Core/Settings.h"
#include <QtWidgets>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

MainWindow::MainWindow() :
        _ui(new Ui::MainWindow) {
    _settings = Settings::instance();
    _process = new QProcess(this);
    _fsModel = new QFileSystemModel;

    _ui->setupUi(this);

    _projectTreeView = new QTreeView;
    _projectTreeView->setFrameShape(QFrame::NoFrame);
    _projectTreeView->setHeaderHidden(true);

    connect(_projectTreeView, &QTreeView::doubleClicked, this, &MainWindow::onFileDoubleClicked);

    _ui->tabWidgetSideBar->addTab(_projectTreeView, tr("Project"));
    _ui->tabWidgetSideBar->addTab(new QWidget, tr("Properties"));

    readSettings();
}

MainWindow::~MainWindow() {
    delete _ui;
    delete _fsModel;
}

void MainWindow::on_actionNewProject_triggered() {
    NewProject newProject(this);
    newProject.exec();
    if (!newProject.projectPath().isEmpty()) {
        openProject(newProject.projectPath());
    }
}

void MainWindow::on_actionNewIrbis_triggered() {
    NewFile newFile(_projectPath);
    newFile.exec();
    if (!newFile.filePath().isEmpty()) {
        addCaveTab(newFile.filePath());
    }
}

void MainWindow::on_actionOpenProject_triggered() {
    QString dirPath = QFileDialog::getExistingDirectory(this, QString(), _settings->readWorkspace());
    if (!dirPath.isEmpty()) {
        openProject(dirPath);
    }
}

void MainWindow::on_actionOpenFile_triggered() {
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open Irbis File"), _projectPath, "Irbis (*.irbis);;All Files(*.*)");
    if (!filePath.isEmpty()) {
        addCaveTab(filePath);
    }
}


void MainWindow::on_actionSaveFileAs_triggered() {
    QString workspaceDir = _settings->readWorkspace();
    QString filePath = QFileDialog::getSaveFileName(this, tr("Save Irbis File"), workspaceDir, "Irbis (*.irbis);;All Files(*.*)");
    if (!filePath.isEmpty()) {
        addCaveTab(filePath);
    }
}

void MainWindow::on_actionCloseProject_triggered() {
    closeProject();
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

void MainWindow::on_actionBuild_triggered() {
    static_cast<Cave*>(_ui->tabWidgetCave->currentWidget())->build();
}

void MainWindow::on_actionStop_triggered() {
    static_cast<Cave*>(_ui->tabWidgetCave->currentWidget())->stop();
}

void MainWindow::on_actionUnitBuilder_triggered() {
    _process->startDetached("unitbuilder");
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
        _projectTreeView->setCurrentIndex(modelIndex);
        changeWindowTitle(filePath);
    } else {
        _projectTreeView->setCurrentIndex(QModelIndex());
        changeWindowTitle();
    }

    _ui->actionSaveFileAs->setEnabled(index >= 0);
    _ui->actionClose->setEnabled(index >= 0);
    _ui->actionCloseOther->setEnabled(index >= 0);
    _ui->actionCloseAll->setEnabled(index >= 0);
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

    openProject(_settings->value("Path/lastProject").toString());
}

void MainWindow::writeSettings() {
    _settings->beginGroup("MainWindow");
    _settings->setValue("size", size());
    _settings->setValue("pos", pos());
    _settings->setValue("splitter", _ui->splitter->saveState());
    _settings->setValue("showSidebar", _ui->actionShowSidebar->isChecked());
    _settings->endGroup();

    _settings->setValue("Path/lastProject", _projectPath);
}

void MainWindow::saveSession() {
    if (!_settings->readRestoreSession() || _projectPath.isEmpty()) {
        return;
    }

    QString sessionPath = _projectPath + "/" + PROJECT_DIRECTORY + "/" + PROJECT_SESSION_FILE;
    QFile saveFile(sessionPath);
    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning() << "Couldn't open session file" << sessionPath;
        return;
    }

    QJsonArray openFiles;
    for (int i = 0; i < _ui->tabWidgetCave->count(); i++) {
        Cave* cave = static_cast<Cave*>(_ui->tabWidgetCave->widget(i));
        openFiles.append(QJsonValue(cave->filePath()));
    }

    QJsonObject obj;
    obj["openFiles"] = openFiles;
    obj["selectedTab"] = _ui->tabWidgetCave->currentIndex();

    QJsonDocument saveDoc(obj);
    saveFile.write(saveDoc.toJson());
}

void MainWindow::restoreSession() {
    if (!_settings->readRestoreSession() || _projectPath.isEmpty()) {
        return;
    }

    QString sessionPath = _projectPath + "/" + PROJECT_DIRECTORY + "/" + PROJECT_SESSION_FILE;
    QFileInfo fi(sessionPath);
    if (!fi.exists()) {
        return;
    }

    QFile loadFile(sessionPath);
    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning() << "Couldn't open session file" << sessionPath;
        return;
    }

    QByteArray saveData = loadFile.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));
    QJsonArray array = loadDoc.object()["openFiles"].toArray();
    int selectedTab = loadDoc.object()["selectedTab"].toInt();
    QString selectedFilePath = array.at(selectedTab).toString();

    for (int i = 0; i < array.count(); i++) {
        QString filePath = array.at(i).toString();
        QFileInfo fi(filePath);
        if (fi.exists()) {
            addCaveTab(filePath);
        }
    }

    _ui->tabWidgetCave->setCurrentIndex(findCave(selectedFilePath));
}

void MainWindow::changeWindowTitle(const QString& filePath) {
    QString title = QApplication::applicationName();
    if (!filePath.isEmpty()) {
        QFileInfo info(filePath);
        title += " - " + info.fileName();
    }
    setWindowTitle(title);
}

void MainWindow::openProject(const QString& projectPath) {
    closeProject();
    _projectPath = projectPath;
    _projectTreeView->setModel(_fsModel);
    _projectTreeView->setRootIndex(_fsModel->setRootPath(projectPath));

    for (int i = 1; i < _fsModel->columnCount(); ++i) {
        _projectTreeView->hideColumn(i);
    }

    restoreSession();
}

void MainWindow::closeProject() {
    saveSession();
    on_actionCloseAll_triggered();
    _projectPath = QString();
    _projectTreeView->setModel(nullptr);
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
    saveSession();
    event->accept();
}
