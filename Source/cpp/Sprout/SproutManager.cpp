#include "SproutManager.h"
#include <QtCore>

SproutManager::SproutManager(const QString& filePath, QObject* parent) :
        QObject(parent),
        filePath(filePath) {

}

SproutManager::~SproutManager() {
    qDebug() << "Destroy Sprout Manager" << filePath;
}

void SproutManager::create() {
    qDebug() << "Create Sprout DB" << filePath;
}
