import QtQuick 2.5
import QtQuick.Dialogs 1.2

FileDialog {
    onVisibleChanged: if (!visible) destroy()
    nameFilters: [ qsTr("Sprout Files (*.sprout)"), qsTr("All files (*)") ]
    Component.onCompleted: open()
}

