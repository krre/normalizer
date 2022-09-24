#include "Utils.h"
#include "Constants.h"

Utils::Utils() {

}

QString Utils::applicationPath(const QString& projectPath) {
    return projectPath + "/" + Const::Project::Target::Application::Source;
}

QString Utils::libraryPath(const QString& projectPath) {
    return projectPath + "/" + Const::Project::Target::Library::Source;
}
