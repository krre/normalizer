#include "MainWindow.h"
#include "SourceEditor.h"
#include "core/Constants.h"
#include "core/Settings.h"
#include "dialog/NewProject.h"
#include "dialog/Options.h"
#include <QtWidgets>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    setWindowTitle(Const::App::Name);
    createWidgets();
    createActions();
    readSettings();
}

MainWindow::~MainWindow() {
}

void MainWindow::closeEvent(QCloseEvent* event) {
    closeWindow();
    event->accept();
}

void MainWindow::onNew() {
    NewProject newProject;

    if (newProject.exec() == QDialog::Rejected) return;

    QDir dir;
    dir.mkpath(newProject.path());

    QFileInfo fi(newProject.path());
    QString filePath = newProject.path() + "/" + fi.baseName() + ".norm";

    NormCommon::Project project;
    project.create(newProject.projectTemplate());
    project.write(filePath, NormCommon::Project::FileFormat::Json);
    qInfo().noquote() << "Project created:" << newProject.path();

    openProject(newProject.path());
}

void MainWindow::onOpen() {
    QString dirPath = QFileDialog::getExistingDirectory(this, tr("Open Norm Project"), Settings::Project::workspace());
    if (dirPath.isEmpty()) return;

    openProject(dirPath);
}

void MainWindow::onClose() {
    closeProject();
}

void MainWindow::onQuit() {
    closeWindow();
    QCoreApplication::quit();
}

void MainWindow::onOptions() {
    Options options;
    options.exec();
}

void MainWindow::onAbout() {
    using namespace Const::App;

    QMessageBox::about(this, tr("About %1").arg(Name),
        tr("<h3>%1 %2 %3</h3>\
           IDE for Norm language<br><br> \
           Based on Qt %4<br> \
           Build on %5 %6<br><br> \
           <a href=%7>%7</a><br><br>Copyright © %8, Vladimir Zarypov")
           .arg(Name, Version, Status, QT_VERSION_STR, BuildDate, BuildTime, Url, CopyrightYear));
}

void MainWindow::onTabClosed(int index) {
    QWidget* widget = tabWidget->widget(index);
    tabWidget->removeTab(index);
    delete widget;
}

void MainWindow::onTabClicked(int index) {
    if (index >= 0) {
        editor = static_cast<SourceEditor*>(tabWidget->widget(index));
        editor->setFocus();
    } else {
        editor = nullptr;
    }
}

int MainWindow::addSourceTab(const QString& filePath) {
    int tabIndex = findSource(filePath);

    if (tabIndex != -1) {
        tabWidget->setCurrentIndex(tabIndex);
        return tabIndex;
    } else {
        QFileInfo fi(filePath);
        editor = new SourceEditor(filePath);
        int index = tabWidget->addTab(editor, fi.baseName());
        tabWidget->setTabToolTip(index, filePath);
        tabWidget->setCurrentIndex(index);

        return index;
    }
}

void MainWindow::createActions() {
    QMenu* fileMenu = menuBar()->addMenu(tr("File"));
    fileMenu->addAction(tr("New..."), this, &MainWindow::onNew, QKeySequence("Ctrl+N"));
    fileMenu->addAction(tr("Open..."), this, &MainWindow::onOpen, QKeySequence("Ctrl+O"));
    fileMenu->addAction(tr("Close"), this, &MainWindow::onClose, QKeySequence("Ctrl+W"));
    fileMenu->addSeparator();
    fileMenu->addAction(tr("Exit"), this, &MainWindow::onQuit, QKeySequence("Ctrl+Q"));

    QMenu* toolsMenu = menuBar()->addMenu(tr("Tools"));
    toolsMenu->addAction(tr("Options..."), this, &MainWindow::onOptions);

    QMenu* helpMenu = menuBar()->addMenu(tr("Help"));
    helpMenu->addAction(tr("About %1...").arg(Const::App::Name), this, &MainWindow::onAbout);
}

void MainWindow::createWidgets() {

}

void MainWindow::createTabWidget() {
    tabWidget = new QTabWidget;
    tabWidget->setMinimumSize(QSize(0, 50));
    tabWidget->setTabsClosable(true);
    tabWidget->setMovable(true);

    connect(tabWidget, &QTabWidget::tabCloseRequested, this, &MainWindow::onTabClosed);
    connect(tabWidget, &QTabWidget::tabBarClicked, this, &MainWindow::onTabClicked);

    setCentralWidget(tabWidget);
}

void MainWindow::removeTabWidget() {
    setCentralWidget(nullptr);
    delete tabWidget;
}

void MainWindow::readSettings() {
    QByteArray geometry = Settings::MainWindow::geometry();

    if (geometry.isEmpty()) {
        const QRect availableGeometry = QGuiApplication::screens().first()->availableGeometry();
        resize(availableGeometry.width() * 0.8, availableGeometry.height() * 0.8);
        move((availableGeometry.width() - width()) / 2, (availableGeometry.height() - height()) / 2);
    } else {
        restoreGeometry(geometry);
    }

    if (Settings::Project::openLastProject()) {
        openProject(Settings::Project::lastProject());
    }
}

void MainWindow::writeSettings() {
    Settings::MainWindow::setGeometry(saveGeometry());
}

void MainWindow::readSession() {
    if (!isProjectActive()) return;
    qInfo().noquote() << "Session readed:" << projectPath;
}

void MainWindow::writeSession() {
    if (!isProjectActive()) return;
    qInfo().noquote() << "Session writed:" << projectPath;
}

void MainWindow::openProject(const QString& path) {
    closeProject();

    if (path.isEmpty()) return;

    createTabWidget();
    projectPath = path;
    qInfo().noquote() << "Project opened:" << path;

    if (Settings::Project::restoreSession()) {
        readSession();
    }
}

void MainWindow::closeProject() {
    if (!isProjectActive()) return;

    if (Settings::Project::restoreSession()) {
        writeSession();
    }

    removeTabWidget();
    qInfo().noquote() << "Project closed:" << projectPath;
    projectPath = QString();
}

bool MainWindow::isProjectActive() const {
    return !projectPath.isEmpty();
}

int MainWindow::findSource(const QString& filePath) {
    for (int i = 0; i < tabWidget->count(); i++) {
        auto editor = static_cast<SourceEditor*>(tabWidget->widget(i));

        if (editor->filePath() == filePath) {
            return i;
        }
    }

    return -1;
}

void MainWindow::closeWindow() {
    Settings::Project::setLastProject(Settings::Project::openLastProject() ? projectPath : QString());
    closeProject();
    writeSettings();
}
