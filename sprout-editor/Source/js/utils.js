.import QtQuick 2.8 as QtQuick

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

function saveGeometry(group) {
    var geometry = {}
    geometry.x = x
    geometry.y = y
    geometry.width = width
    geometry.height = height
    Settings.setMap(group, geometry)
}

function loadGeomerty(group) {
    var geometry = Settings.getMap(group)
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
    Settings.setValue("Gui", "toolspaceWidth", toolTabView.width)
    Settings.setValue("Gui", "showToolspace", toolTabView.visible)
}

function loadGui() {

}

function openSprout(path) {
    if (Core.pathToExt(path) !== "sprout") {
        print("Not Sprout file")
        return
    }

    for (var i = 0; i < editorTabView.count; i++) {
        if (editorTabView.getTab(i).item.path === path) {
            editorTabView.currentIndex = i
            return
        }
    }

    var tab = editorTabView.addTab("")
    tab.loaded.connect(function() { tab.item.updateTabTitle() })
    tab.setSource("qrc:/qml/main/editorspace/Editor3D.qml", { path: path })
    editorTabView.currentIndex = editorTabView.count - 1
    addRecentPath(path)
}

function saveAsSprout(path) {
    if (path.substr(-7) !== ".sprout") {
        path += ".sprout"
    }
    Core.copyFile(editorTabView.currentTab.path, path)
    editorTabView.currentTab.path = path
    editorTabView.getTab(editorTabView.currentIndex).title = Core.pathToFileName(path)
    toolTabView.workspace.selectByPath(path)
    editorTabView.currentTab.load()
    addRecentPath(path, mainMenu.recentFilesModel)
}

function renameSprout(oldPath, newPath) {
    if (editorTabView.currentTab && editorTabView.currentTab.path === oldPath) {
        editorTabView.currentTab.sproutDb.close()
        Core.renameFile(oldPath, newPath)
        editorTabView.currentTab.path = newPath
        editorTabView.getTab(editorTabView.currentIndex).title = Core.pathToFileName(newPath)
        toolTabView.workspace.selectByPath(newPath)
        editorTabView.currentTab.reload()
        mainMenu.recentFilesModel.removeByPath(oldPath)
        addRecentPath(newPath, mainMenu.recentFilesModel)
    } else {
        Core.renameFile(oldPath, newPath)
        toolTabView.workspace.selectByPath(newPath)
    }
}

function addRecentPath(path) {
    var model = mainMenu.recentFilesModel
    // Prevention of duplication of path and raising it on top
    model.removeByPath(path)
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
    var list = Settings.getList("RecentFiles")
    for (var i = 0; i < list.length; i++) {
        var path = list[i]
        if (Core.isFileExists(path)) {
            model.append({ path: path })
        }
    }
}

function loadSession() {
    var restoreLastSession = Settings.getValue("Interface", "restoreLastSession", false)
    if (restoreLastSession) {
        toolComboBox.currentIndex = Settings.getValue("Common", "currentToolTab", 0)

        var openFiles = Settings.getList("OpenFiles")
        if (openFiles && openFiles.length) {
            var currentFile = Settings.getValue("Path", "currentFile")
            var currentIndex = -1
            for (var i = 0; i < openFiles.length; i++) {
                var sprotPath = openFiles[i]
                openSprout(sprotPath)

                if (sprotPath === currentFile) {
                    currentIndex = i
                }
            }

            if (currentIndex !== -1 && currentIndex < editorTabView.count) {
                editorTabView.currentIndex = currentIndex
            }
        }
    }
}

function saveSession() {
    if (Settings.getValue("Interface", "restoreLastSession")) {
        Settings.setValue("Common", "currentToolTab", toolComboBox.currentIndex)

        var list = []
        for (var i = 0; i < editorTabView.count; i++) {
            var editor = editorTabView.getTab(i).item
            list.push(editor.path)
        }

        Settings.setList("OpenFiles", list)
        Settings.setValue("Path", "currentFile", editorTabView.currentTab ? editorTabView.currentTab.path : "")
    }
}
