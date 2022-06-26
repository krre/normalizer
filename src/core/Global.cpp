#include "Global.h"
#include "core/Constants.h"
#include <QtCore>

Global::Global() {

}

QString Global::workspacePath() {
    QSettings settings;
    QString workspace = settings.value(Const::Settings::Project::Workspace).toString();
    return workspace.isEmpty() ? QDir::homePath() + "/" + Const::Project::WorkspaceDir : workspace;
}

bool Global::restoreSession() {
    return true;
}
