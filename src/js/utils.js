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

function saveSettings() {
    saveProject()
    saveGeometry("MainWindow")
    saveGui()
    saveRecentPaths("RecentFiles", mainMenu.recentFilesModel)
    saveRecentPaths("RecentProjects", mainMenu.recentProjectsModel)
    saveSession()
}

function loadSettings() {
    loadGui()
    loadRecentPaths("RecentFiles", mainMenu.recentFilesModel)
    loadRecentPaths("RecentProjects", mainMenu.recentProjectsModel)
    loadSession()
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

function saveGui() {
    Settings.setValue("Gui", "projectTreeWidth", projectTreeView.width)
}

function loadGui() {

}

function openSprout(path) {
    if (Core.pathToExt(path) !== "sprout") {
        openSproutInEditor(path)
        return
    }

    for (var i = 0; i < tabView.count; i++) {
        if (tabView.getTab(i).item.path === path && tabView.getTab(i).item.objectName === "3d") {
            tabView.currentIndex = i
            return
        }
    }

    var properties = {}
    properties.path = path
    var name = Core.urlToFileName(path)
    tabView.addTab(name).setSource("qrc:/qml/main/Editor3D.qml", properties)
    tabView.currentIndex = tabView.count - 1
    addRecentPath(path, mainMenu.recentFilesModel)
}

function openSproutInEditor(path) {
    for (var i = 0; i < tabView.count; i++) {
        if (tabView.getTab(i).item.path === path && tabView.getTab(i).item.objectName === "2d") {
            tabView.currentIndex = i
            return
        }
    }

    var properties = {}
    properties.path = path
    properties.text = Core.loadFile(path)
    var name = Core.urlToFileName(path)
    var tab = tabView.addTab(name)
    tab.setSource("qrc:/qml/main/EditorText.qml", properties)
    tabView.currentIndex = tabView.count - 1
    addRecentPath(path, mainMenu.recentFilesModel)
}

function saveAsSprout(path) {
    if (path.substr(-7) !== ".sprout") {
        path += ".sprout"
    }
    currentTab.path = path
    tabView.getTab(tabView.currentIndex).title = Core.pathToFileName(path)
    currentTab.save()
    addRecentPath(path, mainMenu.recentFilesModel)
}

function saveProject() {
    var list = []
    for (var i = 0; i < tabView.count; i++) {
        var path = tabView.getTab(i).item.path
        list.push(path)
    }

    projectSettings.openFiles = list
    projectSettings.currentFile = currentTab ? currentTab.path : ""
    Core.saveFile(projectPath, JSON.stringify(projectSettings, null, 4))
}

function openProject(path) {
    if (path !== mainRoot.projectPath) {
        projectPath = path
        projectSettings = JSON.parse(Core.loadFile(path))
        var currentIndex = -1
        for (var i = 0; i < projectSettings.openFiles.length; i++) {
            var filePath = projectSettings.openFiles[i]
            if (Core.isFileExists(filePath))
            openSprout(filePath)
            if (projectSettings.currentFile && filePath === projectSettings.currentFile) {
                currentIndex = i
            }
        }

        if (currentIndex !== -1) {
            tabView.currentIndex = currentIndex
        }

        addRecentPath(path, mainMenu.recentProjectsModel)
        saveProject() // for maybe changing in opened file list
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

