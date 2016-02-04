import QtQuick 2.6
import QtQuick.Controls 1.5

TextArea {
    id: root
    property string title: Core.pathToFileName(path) + (isDirty ? "*" : "")
    property bool isDirty: false
    property string path
    objectName: "2d"

    Component.onCompleted: isDirty = false

    onTextChanged: isDirty = true

    onTitleChanged: {
        for (var i = 0; i < tabView.count; i++) {
            var tab = tabView.getTab(i)
            if (root === tab.item) {
                tab.title = title
                break
            }
        }
    }

    function save() {
        Core.saveFile(path, text)
        isDirty = false
    }
}
