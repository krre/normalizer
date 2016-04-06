#include "MainWindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    setWindowTitle("Greenery");

    createActions();

    splitter = new QSplitter;
    setCentralWidget(splitter);

    fileSystemModel = new QFileSystemModel;
    fileSystemModel->setRootPath(QDir::currentPath());
    fileSystemModel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    fileSystemModel->sort(0, Qt::AscendingOrder);

    QTreeView* treeView = new QTreeView;
    treeView->setModel(fileSystemModel);
    treeView->resizeColumnToContents(0);
    treeView->hideColumn(1);
    treeView->hideColumn(2);
    treeView->hideColumn(3);

    workArea = new WorkArea;
    workArea->resize(640, 480);
    splitter->addWidget(treeView);
    // Don't works here. Only after first timer event;
//    splitter->addWidget(workArea);

    readSettings();
    timerId = startTimer(100);
}

void MainWindow::closeEvent(QCloseEvent* event) {
    if (maybeSave()) {
        writeSettings();
        event->accept();
    } else {
        event->ignore();
    }
}

void MainWindow::timerEvent(QTimerEvent*) {
    // Hack to prevent crash application on Windows 10, Qt 5.6.0
    splitter->addWidget(workArea);
    killTimer(timerId);
}

void MainWindow::createActions() {
    QMenu* fileMenu = menuBar()->addMenu(tr("&File"));

    QAction* newAct = new QAction(tr("New"), this);
    newAct->setShortcut(QKeySequence("Ctrl+N"));
    connect(newAct, SIGNAL(triggered(bool)), this, SLOT(newFile()));
    fileMenu->addAction(newAct);

    QAction* openAct = new QAction(tr("Open..."), this);
    openAct->setShortcut(QKeySequence("Ctrl+O"));
    connect(openAct, SIGNAL(triggered(bool)), this, SLOT(open()));
    fileMenu->addAction(openAct);

    QAction* saveAct = new QAction(tr("Save"), this);
    saveAct->setShortcut(QKeySequence("Ctrl+S"));
    connect(saveAct, SIGNAL(triggered(bool)), this, SLOT(save()));
    fileMenu->addAction(saveAct);

    QAction* saveAsAct = new QAction(tr("Save As..."), this);
    saveAsAct->setShortcut(QKeySequence("Ctrl+Shift+S"));
    connect(saveAsAct, SIGNAL(triggered(bool)), this, SLOT(saveAs()));
    fileMenu->addAction(saveAsAct);

    fileMenu->addSeparator();

    QAction* quitAct = new QAction(tr("Exit"), this);
    quitAct->setShortcut(QKeySequence("Ctrl+Q"));
    connect(quitAct, SIGNAL(triggered(bool)), this, SLOT(quitApp()));
    fileMenu->addAction(quitAct);

    QMenu* helpMenu = menuBar()->addMenu(tr("&Help"));

    QAction* aboutAct = new QAction(QString(tr("About %1...")).arg(QCoreApplication::applicationName()), this);
    connect(aboutAct, SIGNAL(triggered(bool)), this, SLOT(about()));
    helpMenu->addAction(aboutAct);

    QAction* aboutQtAct = new QAction(tr("About Qt..."), this);
    connect(aboutQtAct, SIGNAL(triggered(bool)), this, SLOT(aboutQt()));
    helpMenu->addAction(aboutQtAct);
}

void MainWindow::readSettings() {
    QSettings settings(QSettings::IniFormat, QSettings::UserScope, QCoreApplication::organizationName(), QCoreApplication::applicationName());
    const QByteArray geometry = settings.value("geometry", QByteArray()).toByteArray();
    if (geometry.isEmpty()) {
        const QRect availableGeometry = QApplication::desktop()->availableGeometry(this);
        resize(availableGeometry.width() / 3, availableGeometry.height() / 2);
        move((availableGeometry.width() - width()) / 2,
             (availableGeometry.height() - height()) / 2);
    } else {
        restoreGeometry(geometry);
    }

    const QByteArray splitterSizes = settings.value("splitterSizes").toByteArray();
    if (splitterSizes.isEmpty()) {
        QList<int> sizes;
        sizes << 100 << 300;
        splitter->setSizes(sizes);
    } else {
        splitter->restoreState(splitterSizes);
    }
}

void MainWindow::writeSettings() {
    QSettings settings(QSettings::IniFormat, QSettings::UserScope, QCoreApplication::organizationName(), QCoreApplication::applicationName());
    settings.setValue("geometry", saveGeometry());
    settings.setValue("splitterSizes", splitter->saveState());
}

bool MainWindow::maybeSave() {
    return true;
}

void MainWindow::newFile() {
    qDebug() << "new";
}

void MainWindow::open() {
    qDebug() << "open";
}

void MainWindow::save() {
    qDebug() << "save";
}

void MainWindow::saveAs() {
    qDebug() << "save as";
}

void MainWindow::quitApp() {
    QApplication::quit();
}

void MainWindow::about() {
    QMessageBox::about(this, QString(tr("About %1...")).arg(QCoreApplication::applicationName()),
        QString(tr("<h3>%1 %2</h3>"
                  "Based on Qt %3<br>"
                  "Build on %4<br><br>"
                  "<a href=\"https://github.com/krre/greenery\">"
                  "https://github.com/krre/greenery</a><br><br>"
                  "Copyright © 2015-2016, Vladimir Zarypov")).
        arg(QCoreApplication::applicationName()).
        arg(QCoreApplication::applicationVersion()).
        arg(QT_VERSION_STR).
        arg(__DATE__));
}

void MainWindow::aboutQt() {
    QMessageBox::aboutQt(this);
}
