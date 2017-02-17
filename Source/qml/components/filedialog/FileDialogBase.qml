import QtQuick 2.5
import QtQuick.Dialogs 1.2

FileDialog {
    nameFilters: [ qsTr("Sprout Files (*.sprout)"), qsTr("All files (*)") ]
    onVisibleChanged: if (!visible) destroy()
    Component.onCompleted: open()
}

