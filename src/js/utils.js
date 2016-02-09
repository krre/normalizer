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
    saveGeometry("MainWindow")
    saveGui()
    saveRecentPaths()
    saveSession()
}

function loadSettings() {
    loadGui()
    loadRecentPaths()
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
        print("Not Sprout file")
        return
    }

    for (var i = 0; i < tabView.count; i++) {
        if (tabView.getTab(i).item.path === path) {
            tabView.currentIndex = i
            return
        }
    }

    var tab = tabView.addTab("")
    tab.loaded.connect(function() { tab.item.updateTabTitle() })
    tab.setSource("qrc:/qml/main/Editor3D.qml", { path: path })
    tabView.currentIndex = tabView.count - 1
    addRecentPath(path)
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

function addRecentPath(path) {
    var model = mainMenu.recentFilesModel
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

function saveRecentPaths() {
    var model = mainMenu.recentFilesModel
    var list = []
    for (var i = 0; i < model.count; i++) {
        var path = model.get(i).path
        if (path) {
            list.push(path)
        }
    }
    Settings.setList("RecentFiles", list)
}

function loadRecentPaths() {
    var model = mainMenu.recentFilesModel
    var list = Settings.list("RecentFiles")
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
        var openFiles = Settings.list("OpenFiles")
        if (openFiles) {
            var currentFile = Settings.value("Path", "currentFile")
            var currentIndex = -1
            for (var i = 0; i < openFiles.length; i++) {
                var sprotPath = openFiles[i]
                openSprout(sprotPath)

                if (sprotPath === currentFile) {
                    currentIndex = i
                }
            }

            if (currentIndex !== -1 && currentIndex < tabView.count) {
                tabView.currentIndex = currentIndex
            }

            addRecentPath(sprotPath)
        }
    }
}

function saveSession() {
    if (Settings.value("Interface", "restoreLastSession")) {
        var list = []
        for (var i = 0; i < tabView.count; i++) {
            var editor = tabView.getTab(i).item
            list.push(editor.path)
        }

        Settings.setList("OpenFiles", list)
        Settings.setValue("Path", "currentFile", currentTab ? currentTab.path : "")
    }
}

function variantToBool(value) {
    return typeof value === "boolean" ? value : value === "true"
}

