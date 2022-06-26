#include "Global.h"
#include "core/Constants.h"
#include <QtCore>

Global::Global() {

}

QString Global::workspacePath() {
    QSettings settings;
    return settings.value(Const::Settings::Project::Workspace, QDir::homePath() + "/" + Const::Project::WorkspaceDir).toString();
}

bool Global::restoreSession() {
    QSettings settings;
    return settings.value(Const::Settings::Session::Restore, true).toBool();
}
