#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Editor3D.h"
#include "Core/Defines.h"
#include "Core/Settings.h"
#include <QtWidgets>

namespace IrbisUnitBuilder {

MainWindow::MainWindow(const QString& filePath) :
        filePath(filePath),
        ui(new Ui::MainWindow) {
    settings = Settings::instance();

    ui->setupUi(this);

    readSettings();

    if (!filePath.isEmpty()) {
        openFile(filePath);
    }

    updateActions();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent* event) {
    writeSettings();
    event->accept();
}

void MainWindow::on_actionOpen_triggered() {
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open Irbis File"), QString(), "Irbis (*.irbis);;All Files(*.*)");
    if (!filePath.isEmpty()) {
        openFile(filePath);
    }
}

void MainWindow::on_actionClose_triggered() {
    closeFile();
}

void MainWindow::on_actionExit_triggered() {
    QApplication::quit();
}

void MainWindow::on_actionAdd_triggered() {
    editor3d->addUnit();
}

void MainWindow::on_actionRemove_triggered() {
    qDebug() << "remove";
}

void MainWindow::on_actionResetView_triggered() {
    editor3d->resetViewport();
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

void MainWindow::readSettings() {
    settings->beginGroup("MainWindow");

    resize(settings->value("size", QSize(WINDOW_WIDTH, WINDOW_HEIGHT)).toSize());
    move(settings->value("pos", QPoint(WINDOW_X, WINDOW_Y)).toPoint());

    QVariant splitterSize = settings->value("splitter");
    if (splitterSize == QVariant()) {
        ui->splitter->setSizes({ 500, 100 });
    } else {
        ui->splitter->restoreState(splitterSize.toByteArray());
    }

    settings->endGroup();
}

void MainWindow::writeSettings() {
    settings->beginGroup("MainWindow");
    settings->setValue("size", size());
    settings->setValue("pos", pos());
    settings->setValue("splitter", ui->splitter->saveState());
    settings->endGroup();
}

void MainWindow::openFile(const QString& filePath) {
    closeFile();
    this->filePath = filePath;
    editor3d.reset(new Editor3D(filePath));
    ui->splitter->widget(0)->layout()->addWidget(editor3d.data());
    changeWindowTitle(filePath);
    updateActions();
}

void MainWindow::closeFile() {
    filePath = QString();
    editor3d.reset();
    changeWindowTitle();
    updateActions();
}

void MainWindow::changeWindowTitle(const QString& filePath) {
    QString title = QApplication::applicationName();
    if (!filePath.isEmpty()) {
        QFileInfo info(filePath);
        title = info.fileName() + " - " + title;
    }
    setWindowTitle(title);
}

void MainWindow::updateActions() {
    bool isFileOpened = !editor3d.isNull();
    ui->menuView->menuAction()->setVisible(isFileOpened);
    ui->menuUnit->menuAction()->setVisible(isFileOpened);
    ui->actionClose->setEnabled(isFileOpened);
}

} // IrbisUnitBuilder
