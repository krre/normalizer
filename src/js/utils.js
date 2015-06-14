function createDynamicObject(parent, url, properties) {
    var component = Qt.createComponent(url)
    var errorMessage = component.errorString()
    if (errorMessage) {
        print("Error loading component " + url + ":", errorMessage)
    } else {
        return component.createObject(parent, properties ? properties : {})
    }
}

function openFile(path) {
    addRecentFile(path)
    var tab = tabView.addTab(UTILS.urlToFileName(path))
    tab.setSource("qrc:/qml/TreeArea.qml", { filePath: path })
    tabView.currentIndex = tabView.count - 1
}

function saveFile(path) {
    if (path) {
        print("File", path, "saved")
    } else {
        saveAsFile()
    }
}

function saveAsFile() {
    createDynamicObject(mainRoot, "qrc:/qml/components/filedialog/FileDialogSave.qml")
}

function saveAllFiles() {
    for (var i = 0; i < tabView.count; i++) {
        var path = tabView.getTab(i).item.filePath
        if (path) {
            saveFile(path)
        }
    }
}

function addRecentFile(path) {
    var model = topMenuBar.recentFilesModel
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

function saveRecentFiles(model) {
    var list = []
    for (var i = 0; i < model.count; i++) {
        var path = model.get(i).filePath
        if (path) {
            list.push(path)
        }
    }
    SETTINGS.setRecentFiles(list)
}

function loadRecentFiles() {
    var list = SETTINGS.getRecentFiles()
    var model = topMenuBar.recentFilesModel
    for (var i = 0; i < list.length; i++) {
        model.append({ filePath: list[i] })
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
    SETTINGS.setSession(list)
}

function loadSession() {
    var list = SETTINGS.getSession()
    for (var i = 0; i < list.length; i++) {
        openFile(list[i])
    }
}

function saveGeometry() {
    var map = {}
    map.x = mainRoot.x
    map.y = mainRoot.y
    map.width = mainRoot.width
    map.height = mainRoot.height
    SETTINGS.setGeometry(map)
}

function loadGeometry() {
    var map = SETTINGS.getGeometry()
    if (Object.keys(map).length) {
        mainRoot.x = map.x
        mainRoot.y = map.y
        mainRoot.width = map.width
        mainRoot.height = map.height
        return true
    } else {
        return false
    }
}


