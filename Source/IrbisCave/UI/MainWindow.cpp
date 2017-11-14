#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Cave.h"
#include "Core/Defines.h"
#include <QtWidgets>

MainWindow::MainWindow() :
        _ui(new Ui::MainWindow),
        _settings(QCoreApplication::applicationDirPath() + "/" + APP_SETTINGS_NAME, QSettings::IniFormat) {
    _ui->setupUi(this);
    _ui->tabWidget_left_sideBar->setTabText(0, tr("File Browser"));
    _ui->tabWidget_left_sideBar->setTabText(1, tr("Properties"));
    _cave = new Cave;
//    setCentralWidget(_cave);
    readSettings();
}

MainWindow::~MainWindow() {
    delete _ui;
}

void MainWindow::on_actionNew_triggered() {
    QString filePath = QFileDialog::getSaveFileName(this, tr("Create Irbis File"), QString(), "Irbis (*.irbis);;All Files(*.*)");
    if (!filePath.isEmpty()) {
        QFileInfo info(filePath);
        if (info.suffix() != "irbis") {
            filePath += ".irbis";
        }
        changeWindowTitle(filePath);
        _cave->newIrbis(filePath);
    }
}

void MainWindow::on_actionOpen_triggered() {
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open Irbis File"), QString(), "Irbis (*.irbis);;All Files(*.*)");
    if (!filePath.isEmpty()) {
        changeWindowTitle(filePath);
        _cave->openIrbis(filePath);
    }
}

void MainWindow::on_actionSave_As_triggered() {
    QString filePath = QFileDialog::getSaveFileName(this, tr("Save Irbis File"), QString(), "Irbis (*.irbis);;All Files(*.*)");
    if (!filePath.isEmpty()) {
        QFileInfo info(filePath);
        if (info.suffix() != "irbis") {
            filePath += ".irbis";
        }
        changeWindowTitle(filePath);
        _cave->copyIrbis(filePath);
    }
}

void MainWindow::on_actionClose_triggered() {
    _cave->closeIrbis();
    changeWindowTitle();
}

void MainWindow::on_actionExit_triggered() {
    QApplication::quit();
}

void MainWindow::on_actionShow_Left_Sidebar_toggled(bool checked) {
    if (checked) {
        _ui->tabWidget_left_sideBar->show();
    } else {
        _ui->tabWidget_left_sideBar->hide();
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

void MainWindow::readSettings() {
    _settings.beginGroup("MainWindow");

    resize(_settings.value("size", QSize(1000, 600)).toSize());
    move(_settings.value("pos", QPoint(200, 200)).toPoint());

    QVariant splitterSize = _settings.value("splitter");
    if (splitterSize == QVariant()) {
        _ui->splitter->setSizes({ 100, 500 });
    } else {
        _ui->splitter->restoreState(splitterSize.toByteArray());
    }

    _ui->actionShow_Left_Sidebar->setChecked(_settings.value("showLeftSidebar", true).toBool());

    _settings.endGroup();

    _settings.beginGroup("Cave");
    QString filePath = _settings.value("filePath").toString();
    if (!filePath.isEmpty()) {
        changeWindowTitle(filePath);
        _cave->openIrbis(filePath);
    } else {
        changeWindowTitle();
    }
    _settings.endGroup();
}

void MainWindow::writeSettings() {
    _settings.beginGroup("MainWindow");
    _settings.setValue("size", size());
    _settings.setValue("pos", pos());
    _settings.setValue("splitter", _ui->splitter->saveState());
    _settings.setValue("showLeftSidebar", _ui->actionShow_Left_Sidebar->isChecked());
    _settings.endGroup();

    _settings.beginGroup("Cave");
    _settings.setValue("filePath", _cave->filePath());
    _settings.endGroup();
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
