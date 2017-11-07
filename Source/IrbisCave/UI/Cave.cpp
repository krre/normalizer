#include "Cave.h"
#include <QtCore>

Cave::Cave() {

}

Cave::~Cave() {

}

void Cave::setFilePath(const QString& path) {
    m_filePath = path;
}

QString Cave::filePath() const {
    return m_filePath;
}
