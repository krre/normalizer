import QtQuick 2.8
import QtQuick.Controls 1.5

Item {
    height: 120

    function append(message) {
        var time = new Date().toLocaleTimeString()
        var finalMessage = time + ": " + message
        textEdit.append(finalMessage)
    }

    function clear() {
        textEdit.clear()
    }

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

