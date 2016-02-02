.import QtQuick 2.6 as QtQuick

function createDynamicObject(parent, url, properties) {
    var component = Qt.createComponent(url)
    if (component.status === QtQuick.Component.Ready) {
        return component.createObject(parent, properties || {})
    } else {
        print(component.errorString())
    }
}

function Logger() {
    this.isEnabled = true
    this.isInitEnabled = false

    this.log = function (message) {
        if (this.isEnabled) {
            print(message)
        }
    }

    this.initLog = function (message) {
        if (this.isInitEnabled) {
            print(message)
        }
    }
}

function saveGeometry(name) {
    var geometry = {}
    geometry.x = x
    geometry.y = y
    geometry.width = width
    geometry.height = height
    Settings.setMap(name, geometry)
}

function loadGeomerty(name) {
    var geometry = Settings.map(name)
    if (Object.keys(geometry).length) {
        x = geometry.x
        y = geometry.y
        width = geometry.width
        height = geometry.height
    } else if (Screen.width && Screen.height) {
        x = (Screen.width - width) / 2
        y = (Screen.height - height) / 2
    }
}

function openFile(path) {
    addRecentPath(path, mainMenu.recentFilesModel)
}

function openProject(path) {
    if (path !== mainRoot.projectPath) {
        mainRoot.projectPath = path
        addRecentPath(path, mainMenu.recentProjectsModel)
    }
}

function addRecentPath(path, model) {
    // Prevention of duplication of filePath and raising it on top
    for (var i = 0; i < model.count; i++) {
        if (model.get(i).path === path) {
            model.remove(i)
        }
    }
    model.insert(0, { path: path })
    var maxRecentPaths = 10
    if (model.count === maxRecentPaths + 1) {
        model.remove(maxRecentPaths)
    }
}

function saveRecentPaths(group, model) {
    var list = []
    for (var i = 0; i < model.count; i++) {
        var path = model.get(i).path
        if (path) {
            list.push(path)
        }
    }
    Settings.setList(group, list)
}

function loadRecentPaths(group, model) {
    var list = Settings.list(group)
    for (var i = 0; i < list.length; i++) {
        var path = list[i]
        if (Core.isFileExists(path)) {
            model.append({ path: path })
        }
    }
}

function loadSession() {
    var restoreLastSession = variantToBool(Settings.value("Interface", "restoreLastSession", false))
    if (restoreLastSession) {
        var lastProject = Settings.value("Path", "lastProject")
        if (lastProject && Core.isFileExists(lastProject)) {
            openProject(lastProject)
        }
    }
}

function saveSession() {
    if (Settings.value("Interface", "restoreLastSession")) {
        Settings.setValue("Path", "lastProject", projectPath)
    }
}

function variantToBool(value) {
    return typeof value === "boolean" ? value : value === "true"
}

