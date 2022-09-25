#include "GuiSession.h"
#include "core/Constants.h"
#include <QtCore>

GuiSession::GuiSession() {

}

void GuiSession::read(const QString& projectPath) {
    m_projectPath = projectPath;

    QFile file(filePath());

    if (!file.open(QIODevice::ReadOnly)) {
        qWarning().noquote() << "Failed to open project session file for reading:" << filePath();
        return;
    }

    session = QJsonDocument::fromJson(file.readAll()).object();
    qInfo().noquote() << "Session readed:" << projectPath;
}

void GuiSession::write() {
    QFile file(filePath());

    if (!file.open(QIODevice::WriteOnly)) {
        qWarning().noquote() << "Failed to open project session file for writing:" << filePath();
        return;
    }

    file.write(QJsonDocument(session).toJson());
    qInfo().noquote() << "Session writed:" << m_projectPath;
}

QString GuiSession::dirPath() const {
    return m_projectPath + "/" + Const::Project::DataDir;
}

QString GuiSession::filePath() const {
    return dirPath() + "/" + Const::Project::SessionFile;
}
