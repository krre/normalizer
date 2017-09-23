#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "../Defines.h"
#include "Editor3D.h"
#include <QtWidgets>

MainWindow::MainWindow() :
        ui(new Ui::MainWindow),
        settings(QCoreApplication::applicationDirPath() + "/" + "sproute.ini", QSettings::IniFormat) {
    ui->setupUi(this);
    setWindowTitle(QApplication::applicationName());
    readSettings();
}

MainWindow::~MainWindow() {
    writeSettings();
    delete ui;
}

void MainWindow::on_actionNew_triggered() {
    QString filePath = QFileDialog::getSaveFileName(this, tr("Create new Sprout file"), QString(), "Sprout (*.sprout)");
    createEditor3D(filePath, true);
}

void MainWindow::on_actionOpen_triggered() {
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open Sprout file"), QString(), "Sprout (*.sprout);;All Files(*.*)");
    createEditor3D(filePath, false);
}

void MainWindow::on_actionExit_triggered() {
    QApplication::quit();
}

void MainWindow::on_actionAbout_triggered() {
    QMessageBox::about(this, tr("About %1").arg(APP_NAME),
        tr("<h3>%1 %2</h3> \
           Based on Qt %3<br> \
           Build on %4<br><br> \
           <a href=%5>%5</a><br><br> \
           Copyright © 2015-2017, Vladimir Zarypov").
           arg(APP_NAME).arg(APP_VERSION_STR).arg(QT_VERSION_STR).arg(__DATE__).arg(APP_URL));
}

void MainWindow::on_actionShow_left_sidebar_toggled(bool checked) {
    if (checked) {
        ui->listView->show();
    } else {
        ui->listView->hide();
    }
}

void MainWindow::on_tabWidget_tabCloseRequested(int index) {
    delete ui->tabWidget->widget(index);
    ui->tabWidget->removeTab(index);
}

void MainWindow::readSettings() {
    settings.beginGroup("MainWindow");
    resize(settings.value("size", QSize(1000, 600)).toSize());
    move(settings.value("pos", QPoint(200, 200)).toPoint());
    QVariant splitterSize = settings.value("splitter");
    if (splitterSize == QVariant()) {
        ui->splitter->setSizes({ 100, 500 });
    } else {
        ui->splitter->restoreState(splitterSize.toByteArray());
    }
    ui->actionShow_left_sidebar->setChecked(settings.value("showLeftSidebar").toBool());
    settings.endGroup();

    settings.beginGroup("Path");
    QString lastFilePath = settings.value("lastSproutPath").toString();
    if (QFile::exists(lastFilePath)) {
        createEditor3D(lastFilePath, false);
    }

    settings.endGroup();
}

void MainWindow::writeSettings() {
    settings.beginGroup("MainWindow");
    settings.setValue("size", size());
    settings.setValue("pos", pos());
    settings.setValue("splitter", ui->splitter->saveState());
    settings.setValue("showLeftSidebar", ui->actionShow_left_sidebar->isChecked());
    settings.endGroup();

    if (ui->tabWidget->count()) {
        settings.beginGroup("Path");
        Editor3D* editor = static_cast<Editor3D*>(ui->tabWidget->widget(0));
        settings.setValue("lastSproutPath", editor->getFilePath());
        settings.endGroup();
    }
}

void MainWindow::createEditor3D(const QString& filePath, bool isNew) {
    if (!filePath.isEmpty()) {
        QFileInfo fi(filePath);
        int index = ui->tabWidget->addTab(new Editor3D(filePath), fi.fileName());
        Editor3D* editor = static_cast<Editor3D*>(ui->tabWidget->widget(index));
        if (isNew) {
            editor->getSproutManager()->create();
        } else {
            editor->getSproutManager()->open();
        }
        editor->load();
    }
}
