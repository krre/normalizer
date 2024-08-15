#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "../Defines.h"
#include "SelectWorkspace.h"
#include "Editor3D.h"
#include "Options.h"
#include <QtWidgets>

MainWindow::MainWindow() :
        ui(new Ui::MainWindow),
        settings(QCoreApplication::applicationDirPath() + "/" + SETTINGS_NAME, QSettings::IniFormat) {
    ui->setupUi(this);
    setWindowTitle(QApplication::applicationName());
    toggleMenusVisible(false);
    readSettings();
}

MainWindow::~MainWindow() {
    writeSettings();
    delete ui;
}

bool MainWindow::selectWorkspace() {
    bool result = true;
    if (!settings.contains("Path/workspace")) {
        SelectWorkspace dialog(this);
        connect(&dialog, &QDialog::rejected, this, [&] () {
            result = false;
        });
        dialog.exec();
    }

    return result;
}

void MainWindow::on_actionNew_triggered() {
    const QString workspace = settings.value("Path/workspace").toString();
    QString filePath = QFileDialog::getSaveFileName(this, tr("Create new Sprout file"), workspace, "Sprout (*.sprout)");
    createEditor3D(filePath, true);
}

void MainWindow::on_actionOpen_triggered() {
    const QString workspace = settings.value("Path/workspace").toString();
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open Sprout file"), workspace, "Sprout (*.sprout);;All Files(*.*)");
    int index = findSproutFile(filePath);
    if (index >= 0) {
        ui->tabWidget->setCurrentIndex(index);
    } else {
        createEditor3D(filePath, false);
    }
}

void MainWindow::on_actionClose_triggered() {
    on_tabWidget_tabCloseRequested(ui->tabWidget->currentIndex());
}

void MainWindow::on_actionClose_All_triggered() {
    while (ui->tabWidget->count()) {
        on_tabWidget_tabCloseRequested(0);
    }
}

void MainWindow::on_actionClose_Other_triggered() {
    int i = 0;
    while (ui->tabWidget->count() > 1) {
        if (i != ui->tabWidget->currentIndex()) {
            on_tabWidget_tabCloseRequested(i);
        } else {
            i++;
        }
    }
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

void MainWindow::on_actionBuild_triggered() {
    qDebug() << "Build" << currentEditor3D->getFilePath();
}

void MainWindow::on_actionOptions_triggered() {
    Options options(this);
    options.exec();
}

void MainWindow::on_tabWidget_tabCloseRequested(int index) {
    QWidget* widget = ui->tabWidget->widget(index);
    ui->tabWidget->removeTab(index);
    delete widget;
    tabCountChanged(ui->tabWidget->count());
}

void MainWindow::on_tabWidget_currentChanged(int index) {
    toggleMenusVisible(index >= 0);
    toggleActionEnable(index >= 0);
    currentEditor3D = index >= 0 ? static_cast<Editor3D*>(ui->tabWidget->widget(index)) : nullptr;
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
    bool resoreSession = settings.value("restoreSession").toBool();
    settings.endGroup();

    if (resoreSession) {
        int size = settings.beginReadArray("OpenFiles");
        for (int i = 0; i < size; ++i) {
            settings.setArrayIndex(i);
            const QString path = settings.value("path").toString();
            if (QFile::exists(path)) {
                createEditor3D(path, false);
            }
        }
        settings.endArray();
    }

    QString currentSproutPath = settings.value("Path/currentSproutPath").toString();
    int index = findSproutFile(currentSproutPath);
    if (index >= 0) {
        ui->tabWidget->setCurrentIndex(index);
    }
}

void MainWindow::writeSettings() {
    settings.beginGroup("MainWindow");
    settings.setValue("size", size());
    settings.setValue("pos", pos());
    settings.setValue("splitter", ui->splitter->saveState());
    settings.setValue("showLeftSidebar", ui->actionShow_left_sidebar->isChecked());
    settings.endGroup();

    settings.beginGroup("Path");
    if (ui->tabWidget->count()) {
        Editor3D* editor = static_cast<Editor3D*>(ui->tabWidget->currentWidget());
        settings.setValue("currentSproutPath", editor->getFilePath());
    } else {
        settings.remove("currentSproutPath");
    }
    settings.endGroup();

    settings.remove("OpenFiles");
    settings.beginWriteArray("OpenFiles");
    for (int i = 0; i < ui->tabWidget->count(); i++) {
        settings.setArrayIndex(i);
        Editor3D* editor = static_cast<Editor3D*>(ui->tabWidget->widget(i));
        settings.setValue("path", editor->getFilePath());
    }
    settings.endArray();
}

void MainWindow::toggleMenusVisible(bool visible) {
    ui->menuBuild->menuAction()->setVisible(visible);
    ui->actionBuild->setEnabled(visible);
}

void MainWindow::toggleActionEnable(bool enable) {
    ui->actionSave_as->setEnabled(enable);
    ui->actionClose->setEnabled(enable);
    ui->actionClose_All->setEnabled(enable);
}

void MainWindow::tabCountChanged(int count) {
    ui->actionClose_Other->setEnabled(count > 1);
}

int MainWindow::findSproutFile(const QString& filePath) {
    for (int i = 0; i < ui->tabWidget->count(); i++) {
        Editor3D* editor = static_cast<Editor3D*>(ui->tabWidget->widget(i));
        if (editor->getFilePath() == filePath) {
            return i;
        }
    }

    return -1;
}

void MainWindow::createEditor3D(const QString& filePath, bool isNew) {
    if (!filePath.isEmpty()) {
        QFileInfo fi(filePath);
        int index = ui->tabWidget->addTab(new Editor3D(filePath), fi.fileName());
        tabCountChanged(ui->tabWidget->count());
        ui->tabWidget->setCurrentIndex(index);
        if (isNew) {
            currentEditor3D->getSproutManager()->create();
        } else {
            currentEditor3D->getSproutManager()->open();
        }
        currentEditor3D->load();
    }
}
