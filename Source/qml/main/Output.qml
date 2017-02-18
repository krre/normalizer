import QtQuick 2.8
import QtQuick.Controls 1.5

TextArea {
    height: 120
    readOnly: true
    activeFocusOnPress: false

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
