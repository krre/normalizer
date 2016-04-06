#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    setWindowTitle("Greenery");

    QScreen* screen = QGuiApplication::primaryScreen();
    QSize screenSize = screen->size();
    int width = 800;
    int height = 600;
    int x = (screenSize.width() - width) / 2;
    int y = (screenSize.height() - height) / 2;
    setGeometry(x, y, width, height);

    splitter = new QSplitter(this);

    QTreeView* treeview = new QTreeView;
    workArea = new WorkArea;
    splitter->addWidget(treeview);
    splitter->addWidget(workArea);

    QList<int> sizes;
    sizes << 100 << 300;
    splitter->setSizes(sizes);

    setCentralWidget(splitter);

    createActions();
    createMenus();
}

void MainWindow::createActions() {
    newAct = new QAction(tr("New"), this);
    newAct->setShortcut(QKeySequence("Ctrl+N"));
    connect(newAct, SIGNAL(triggered(bool)), this, SLOT(newFile()));

    openAct = new QAction(tr("Open..."), this);
    openAct->setShortcut(QKeySequence("Ctrl+O"));
    connect(openAct, SIGNAL(triggered(bool)), this, SLOT(open()));

    saveAct = new QAction(tr("Save"), this);
    saveAct->setShortcut(QKeySequence("Ctrl+S"));
    connect(saveAct, SIGNAL(triggered(bool)), this, SLOT(save()));

    saveAsAct = new QAction(tr("Save As..."), this);
    saveAsAct->setShortcut(QKeySequence("Ctrl+Shift+S"));
    connect(saveAsAct, SIGNAL(triggered(bool)), this, SLOT(saveAs()));

    quitAct = new QAction(tr("Exit"), this);
    quitAct->setShortcut(QKeySequence("Ctrl+Q"));
    connect(quitAct, SIGNAL(triggered(bool)), this, SLOT(quitApp()));

    aboutAct = new QAction(QString(tr("About %1...")).arg(QCoreApplication::applicationName()), this);
    connect(aboutAct, SIGNAL(triggered(bool)), this, SLOT(about()));

    aboutQtAct = new QAction(tr("About Qt..."), this);
    connect(aboutQtAct, SIGNAL(triggered(bool)), this, SLOT(aboutQt()));
}

void MainWindow::createMenus() {
    fileMenu = menuBar()->addMenu(tr("File"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveAsAct);
    fileMenu->addSeparator();
    fileMenu->addAction(quitAct);

    helpMenu = menuBar()->addMenu(tr("Help"));
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);
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
