function createDynamicObject(parent, url, properties) {
    var component = Qt.createComponent(url)
    var errorMessage = component.errorString()
    if (errorMessage) {
        print("Error loading component " + url + ":", errorMessage)
    } else {
        return component.createObject(parent, properties ? properties : {})
    }
}

function newFile(directory, file, name) {
    var path = directory + "/" + file + ".sprout"
    PROJECT.create(path, name.text)

    var tab = tabView.addTab(name)
    tab.setSource("qrc:/qml/WorkArea.qml", { filePath: path })
    tabView.currentIndex = tabView.count - 1
    addRecentFile(path)
    SETTINGS.setRecentDirectory(directory.text)
}

function openFile(path) {
    var projectName = UTILS.urlToFileName(path)
    var tab = tabView.addTab(projectName)
    tab.setSource("qrc:/qml/WorkArea.qml", { filePath: path, projectName: projectName })
    tabView.currentIndex = tabView.count - 1
    addRecentFile(path)
}

function saveAsFile() {
    var fileDialog = createDynamicObject(mainRoot, "qrc:/qml/components/filedialog/FileDialogSave.qml")
    fileDialog.accepted.connect(function() {
        var path = UTILS.urlToPath(fileDialog.fileUrl)
        if (path.substr(-7) !== ".sprout") {
            path += ".sprout"
        }
        currentTab.filePath = path
        tabView.getTab(tabView.currentIndex).title = UTILS.urlToFileName(path)
        addRecentFile(path)
    })
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
