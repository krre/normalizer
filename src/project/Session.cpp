#include "Session.h"
#include "core/Constants.h"
#include <QDir>
#include <QJsonObject>

Session::Session(QObject* parent) : QObject(parent) {

}

void Session::create(const QString& projectPath) {
    m_dirPath = projectPath + "/." + QString(Const::App::Name).toLower();

    QDir dir(m_dirPath);
    dir.mkpath(m_dirPath);
}
