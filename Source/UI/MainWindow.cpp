#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Options.h"
#include "NewProject.h"
#include "NewFile.h"
#include "Cave.h"
#include "ProjectTreeView.h"
#include "Core/Defines.h"
#include "Core/Settings.h"
#include <QtWidgets>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

MainWindow::MainWindow() :
        ui(new Ui::MainWindow) {
    settings = Settings::instance();
    process = new QProcess(this);
    fsModel.reset(new QFileSystemModel);

    ui->setupUi(this);

    projectTreeView = new ProjectTreeView;

    connect(projectTreeView, &ProjectTreeView::openActivated, this, &MainWindow::addCaveTab);
    connect(projectTreeView, &ProjectTreeView::removeActivated, this, &MainWindow::onFileRemoved);

    ui->tabWidgetSideBar->addTab(projectTreeView, tr("Project"));
    ui->tabWidgetSideBar->addTab(new QWidget, tr("Properties"));

    ui->tabWidgetOutput->tabBar()->setVisible(false);

    readSettings();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_actionNewProject_triggered() {
    NewProject newProject(this);
    newProject.exec();
    if (!newProject.projectPath().isEmpty()) {
        openProject(newProject.projectPath());
    }
}

void MainWindow::on_actionNewIrbis_triggered() {
    NewFile newFile(projectPath);
    newFile.exec();
    if (!newFile.filePath().isEmpty()) {
        addCaveTab(newFile.filePath());
    }
}

void MainWindow::on_actionOpenProject_triggered() {
    QString dirPath = QFileDialog::getExistingDirectory(this, QString(), settings->readWorkspace());
    if (!dirPath.isEmpty()) {
        openProject(dirPath);
    }
}

void MainWindow::on_actionOpenFile_triggered() {
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open Irbis File"), projectPath, "Irbis (*.irbis);;All Files(*.*)");
    if (!filePath.isEmpty()) {
        addCaveTab(filePath);
    }
}


void MainWindow::on_actionSaveFileAs_triggered() {
    QString filePath = QFileDialog::getSaveFileName(this, tr("Save Irbis File"), projectPath, "Irbis (*.irbis);;All Files(*.*)");
    if (!filePath.isEmpty()) {
        addCaveTab(filePath);
    }
}

void MainWindow::on_actionCloseProject_triggered() {
    closeProject();
}

void MainWindow::on_actionClose_triggered() {
    on_tabWidgetCave_tabCloseRequested(ui->tabWidgetCave->currentIndex());
}

void MainWindow::on_actionCloseAll_triggered() {
    while (ui->tabWidgetCave->count()) {
        on_tabWidgetCave_tabCloseRequested(0);
    }
}

void MainWindow::on_actionCloseOther_triggered() {
    int i = 0;
    while (ui->tabWidgetCave->count() > 1) {
        if (i != ui->tabWidgetCave->currentIndex()) {
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
    static_cast<Cave*>(ui->tabWidgetCave->currentWidget())->build();
}

void MainWindow::on_actionStop_triggered() {
    static_cast<Cave*>(ui->tabWidgetCave->currentWidget())->stop();
}

void MainWindow::on_actionUnitBuilder_triggered() {
    QStringList arguments;
    if (ui->tabWidgetCave->count()) {
        arguments << static_cast<Cave*>(ui->tabWidgetCave->currentWidget())->filePath();
    }
    process->startDetached(QCoreApplication::applicationDirPath() + "/unitbuilder", arguments);
}

void MainWindow::on_actionOptions_triggered() {
    Options options(this);
    options.exec();
}

void MainWindow::on_actionShowSidebar_toggled(bool checked) {
    if (checked) {
        ui->tabWidgetSideBar->show();
    } else {
        ui->tabWidgetSideBar->hide();
    }
}

void MainWindow::on_actionShowOutput_toggled(bool checked) {
    if (checked) {
        ui->tabWidgetOutput->show();
    } else {
        ui->tabWidgetOutput->hide();
    }
}

void MainWindow::on_actionAbout_triggered() {
    QMessageBox::about(this, tr("About %1").arg(APP_NAME),
        tr("<h3>%1 %2</h3> \
           Based on Qt %3<br> \
           Build on %4<br><br> \
           <a href=%5>%5</a><br><br>%6").
           arg(APP_NAME).arg(APP_VERSION_STR).arg(QT_VERSION_STR).
           arg(__DATE__).arg(APP_URL).arg(APP_COPYRIGHT));
}

void MainWindow::on_tabWidgetCave_tabCloseRequested(int index) {
    QWidget* widget = ui->tabWidgetCave->widget(index);
    ui->tabWidgetCave->removeTab(index);
    delete widget;

    widget = ui->tabWidgetOutput->widget(index);
    ui->tabWidgetOutput->removeTab(index);
    delete widget;
}

void MainWindow::on_tabWidgetCave_currentChanged(int index) {
    if (index >= 0) {
        QString filePath = static_cast<Cave*>(ui->tabWidgetCave->widget(index))->filePath();
        QModelIndex modelIndex = fsModel->index(filePath);
        projectTreeView->setCurrentIndex(modelIndex);
        ui->tabWidgetOutput->setCurrentIndex(index);
        changeWindowTitle(filePath);
    } else {
        projectTreeView->setCurrentIndex(QModelIndex());
        changeWindowTitle();
    }

    ui->actionSaveFileAs->setEnabled(index >= 0);
    ui->actionClose->setEnabled(index >= 0);
    ui->actionCloseOther->setEnabled(index >= 0);
    ui->actionCloseAll->setEnabled(index >= 0);
}

void MainWindow::onFileDoubleClicked(const QModelIndex& index) {
    addCaveTab(fsModel->filePath(index));
}

void MainWindow::onFileRemoved(const QString& filePath) {
    on_tabWidgetCave_tabCloseRequested(findCave(filePath));
    QDir dir;
    dir.remove(filePath);
}

void MainWindow::readSettings() {
    settings->beginGroup("MainWindow");

    resize(settings->value("size", QSize(WINDOW_WIDTH, WINDOW_HEIGHT)).toSize());
    move(settings->value("pos", QPoint(WINDOW_X, WINDOW_Y)).toPoint());

    QVariant splitterMainSize = settings->value("splitterMain");
    if (splitterMainSize == QVariant()) {
        ui->splitterMain->setSizes({ 100, 500 });
    } else {
        ui->splitterMain->restoreState(splitterMainSize.toByteArray());
    }

    QVariant splitterRightSize = settings->value("splitterRight");
    if (splitterRightSize == QVariant()) {
        ui->splitterRight->setSizes({ 500, 100 });
    } else {
        ui->splitterRight->restoreState(splitterRightSize.toByteArray());
    }

    ui->actionShowSidebar->setChecked(settings->value("showSidebar", true).toBool());
    ui->actionShowOutput->setChecked(settings->value("showOutput", true).toBool());

    settings->endGroup();

    QString lastProject = settings->value("Path/lastProject").toString();
    if (!lastProject.isEmpty()) {
        openProject(lastProject);
    }
}

void MainWindow::writeSettings() {
    settings->beginGroup("MainWindow");
    settings->setValue("size", size());
    settings->setValue("pos", pos());
    settings->setValue("splitterMain", ui->splitterMain->saveState());
    settings->setValue("splitterRight", ui->splitterRight->saveState());
    settings->setValue("showSidebar", ui->actionShowSidebar->isChecked());
    settings->setValue("showOutput", ui->actionShowOutput->isChecked());
    settings->endGroup();

    settings->setValue("Path/lastProject", projectPath);
}

void MainWindow::saveSession() {
    if (!settings->readRestoreSession() || projectPath.isEmpty()) {
        return;
    }

    QString sessionPath = projectPath + "/" + PROJECT_DIRECTORY + "/" + PROJECT_SESSION_FILE;
    QFile saveFile(sessionPath);
    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning() << "Couldn't open session file" << sessionPath;
        return;
    }

    QJsonArray openFiles;
    for (int i = 0; i < ui->tabWidgetCave->count(); i++) {
        Cave* cave = static_cast<Cave*>(ui->tabWidgetCave->widget(i));
        openFiles.append(QJsonValue(cave->filePath()));
    }

    QJsonObject obj;
    obj["openFiles"] = openFiles;
    obj["selectedTab"] = ui->tabWidgetCave->currentIndex();

    QJsonDocument saveDoc(obj);
    saveFile.write(saveDoc.toJson());
}

void MainWindow::restoreSession() {
    if (!settings->readRestoreSession() || projectPath.isEmpty()) {
        return;
    }

    QString sessionPath = projectPath + "/" + PROJECT_DIRECTORY + "/" + PROJECT_SESSION_FILE;
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

    ui->tabWidgetCave->setCurrentIndex(findCave(selectedFilePath));
}

void MainWindow::changeWindowTitle(const QString& filePath) {
    QString title = QApplication::applicationName();

    if (!projectPath.isEmpty()) {
        QFileInfo fi(projectPath);
        title = fi.baseName() + " - " + title;
    }

    if (!filePath.isEmpty()) {
        QFileInfo fi(filePath);
        title = fi.fileName() + " - " + title;
    }

    setWindowTitle(title);
}

void MainWindow::openProject(const QString& filePath) {
    closeProject();
    projectPath = filePath;
    projectTreeView->setModel(fsModel.data());
    projectTreeView->setRootIndex(fsModel->setRootPath(filePath));

    for (int i = 1; i < fsModel->columnCount(); ++i) {
        projectTreeView->hideColumn(i);
    }

    restoreSession();

    if (!ui->tabWidgetCave->count()) {
        changeWindowTitle();
    }
}

void MainWindow::closeProject() {
    saveSession();
    on_actionCloseAll_triggered();
    projectPath = QString();
    projectTreeView->setModel(nullptr);
    changeWindowTitle();
}

void MainWindow::addCaveTab(const QString& filePath) {
    QString fullIrbisPath = filePath;
    QFileInfo info(fullIrbisPath);
    if (info.suffix() != "irbis") {
        fullIrbisPath += ".irbis";
    }

    int tabIndex = findCave(fullIrbisPath);
    if (tabIndex != -1) {
        ui->tabWidgetCave->setCurrentIndex(tabIndex);
        ui->tabWidgetOutput->setCurrentIndex(tabIndex);
    } else {
        QFileInfo fi(fullIrbisPath);
        Cave* cave = new Cave(fullIrbisPath);
        int index = ui->tabWidgetCave->addTab(cave, fi.fileName());
        ui->tabWidgetCave->setTabToolTip(index, fullIrbisPath);
        ui->tabWidgetCave->setCurrentIndex(index);

        QTextEdit* textEdit = new QTextEdit;
        textEdit->setReadOnly(true);
        textEdit->setFrameStyle(QFrame::NoFrame);
        ui->tabWidgetOutput->addTab(textEdit, fi.fileName());
        connect(cave, &Cave::outputMessage, textEdit, &QTextEdit::append);
    }
}

int MainWindow::findCave(const QString& filePath) {
    for (int i = 0; i < ui->tabWidgetCave->count(); i++) {
        Cave* cave = static_cast<Cave*>(ui->tabWidgetCave->widget(i));
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
