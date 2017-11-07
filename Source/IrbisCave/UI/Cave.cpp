#include "Cave.h"
#include <QtCore>

Cave::Cave() {

}

Cave::~Cave() {

}

void Cave::newIrbis(const QString& path) {
    m_filePath = path;
    qDebug() << m_filePath;
}

void Cave::openIrbis(const QString& path) {
    m_filePath = path;
    qDebug() << m_filePath;
}

void Cave::copyIrbis(const QString& path) {
    m_filePath = path;
}

QString Cave::filePath() const {
    return m_filePath;
}
