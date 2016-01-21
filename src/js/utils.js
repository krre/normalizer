function createDynamicObject(parent, url, properties) {
    var component = Qt.createComponent(url)
    var errorMessage = component.errorString()
    if (errorMessage) {
        print(errorMessage)
    } else {
        return component.createObject(parent, properties || {})
    }
}

function newFile(directory, name) {
    var path = directory + "/" + name + ".sprout"
    var obj = {}
    obj.name = name
    saveFile(path, obj)
    var tab = tabView.addTab(name)
    tab.setSource("qrc:/qml/main/WorkArea.qml", { filePath: path })
    tabView.currentIndex = tabView.count - 1
    addRecentFile(path)
    Settings.setValue("Path", "recentDirectory", directory)
}

function openFile(path) {
    for (var i = 0; i < tabView.count; i++) {
        if (tabView.getTab(i).item.filePath === path) {
            createDynamicObject(mainRoot, "qrc:/qml/components/messagedialog/MessageDialogError.qml", { text: qsTr("File already loaded") })
            return
        }
    }

    var projectName = Core.urlToFileName(path)
    var tab = tabView.addTab(projectName)
    tab.setSource("qrc:/qml/main/WorkArea.qml", { filePath: path, projectName: projectName })
    tabView.currentIndex = tabView.count - 1
    addRecentFile(path)
}

function saveFile(path, model) {
    Core.saveFile(path, JSON.stringify(model, "", 4))
}

function addRecentFile(path) {
    var model = mainMenu.recentFilesModel
    // Prevention of duplication of filePath and raising it on top.
    for (var i = 0; i < model.count; i++) {
        if (model.get(i).filePath === path) {
            model.remove(i)
        }
    }
    model.insert(0, { filePath: path })
    var maxRecentFiles = 10
    if (model.count === maxRecentFiles + 1) {
        model.remove(maxRecentFiles)
    }
}

function saveRecentFiles() {
    var model = mainMenu.recentFilesModel
    var list = []
    for (var i = 0; i < model.count; i++) {
        var path = model.get(i).filePath
        if (path) {
            list.push(path)
        }
    }
    Settings.setList("RecentFiles", list)
}

function loadRecentFiles() {
    var list = Settings.list("RecentFiles")
    var model = mainMenu.recentFilesModel
    for (var i = 0; i < list.length; i++) {
        var path = list[i]
        if (Core.isFileExists(path)) {
            model.append({ filePath: path })
        }
    }
}

function saveSession() {
    var list = []
    for (var i = 0; i < tabView.count; i++) {
        var path = tabView.getTab(i).item.filePath
        if (path) {
            list.push(path)
        }
    }
    Settings.setList("Session", list)
}

function loadSession() {
    var list = Settings.list("Session")
    if (list) {
        for (var i = 0; i < list.length; i++) {
            var path = list[i]
            if (Core.isFileExists(path)) {
                openFile(list[i])
            }
        }
    }
}
