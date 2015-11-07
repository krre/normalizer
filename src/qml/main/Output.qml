import QtQuick 2.5
import QtQuick.Controls 1.4

Item {
    property alias textEdit: textEdit
    height: 120

    Rectangle {
        anchors.fill: parent
        color: "black"
        opacity: 0.5
    }

    TextEdit {
        id: textEdit
        anchors.fill: parent
        anchors.margins: 5
        verticalAlignment: lineCount < 7 ? TextEdit.AlignTop : TextEdit.AlignBottom
        color: "white"
        opacity: 0.8
        clip: true
        readOnly: true
        selectByMouse: false
        activeFocusOnPress: false
    }
}

