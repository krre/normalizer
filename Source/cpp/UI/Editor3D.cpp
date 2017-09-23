#include "Editor3D.h"
#include <QDebug>

Editor3D::Editor3D(const QString& filePath) :
    filePath(filePath),
    sproutManager(new SproutManager(filePath, this)) {
}

Editor3D::~Editor3D() {
    qDebug() << "Destroy" << filePath;
}
