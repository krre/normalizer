import QtQuick 2.6
import QtQuick.Controls 1.5

TextArea {
    property bool isDirty: false
    property string path
    objectName: "2d"

    onTextChanged: isDirty = true
}
