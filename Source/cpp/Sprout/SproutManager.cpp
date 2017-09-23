#include "SproutManager.h"
#include <QtCore>

SproutManager::SproutManager(const QString& filePath, QObject* parent) : QObject(parent) {
    qDebug() << "Sprout DB" << filePath;
}

SproutManager::~SproutManager() {
    qDebug() << "Destroy Sprout Manager";
}
