import QtQuick 2.8
import QtQuick.Controls 1.5
import QtQuick.Controls.Styles 1.4
import "../../js/style.js" as Style

TextArea {
    height: 120
    readOnly: true
    activeFocusOnPress: false
    style: TextAreaStyle {
        textColor: "white"
        backgroundColor: Style.editor3DBackground
    }

    function appendMessage(message) {
        if (!message) {
            newLine()
        } else {
            var time = new Date().toLocaleTimeString()
            var finalMessage = time + ": " + message
            append(finalMessage)
        }
    }

    function newLine() {
       append("")
    }

    function clear() {
        cursorPosition = 0
        text = ""
    }
}
