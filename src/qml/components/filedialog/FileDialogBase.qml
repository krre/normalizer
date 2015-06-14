import QtQuick 2.5
import QtQuick.Dialogs 1.2

FileDialog {
    id: root
    onVisibleChanged: if (!visible) root.destroy()
    nameFilters: qsTr("Sprout Files (*.sprout)")
    Component.onCompleted: open()
}

