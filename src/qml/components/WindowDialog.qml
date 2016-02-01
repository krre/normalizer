import QtQuick 2.6
import QtQuick.Controls 1.5
import QtQuick.Layouts 1.2
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import "../../js/utils.js" as Utils

Window {
    default property alias data: content.data
    property real indent: 10
    property int standardButtons: StandardButton.Ok | StandardButton.Cancel
    property bool stayOnScreen: false
    property alias okButton: okButton
    property bool hideButtons: false
    property string settingsGroup
    id: root
    width: 500
    height: 500
    minimumWidth: 200
    minimumHeight: 200
    visible: true
    modality: Qt.ApplicationModal
    color: sysPalette.window

    signal accepted
    signal rejected

    Component.onCompleted: {
        if (settingsGroup) {
            Utils.loadGeomerty(settingsGroup)
        }
    }

    Component.onDestruction: {
        if (settingsGroup) {
            Utils.saveGeometry(settingsGroup)
        }
    }

    onVisibleChanged: if (!visible) root.destroy()

    Action {
        shortcut: "Esc"
        onTriggered: root.destroy()
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: indent
        Layout.alignment: Qt.AlignHCenter
        spacing: 7

        Item {
            id: content
            Layout.preferredWidth: parent.width
            Layout.fillHeight: true
            clip: true
        }

        RowLayout {
            Layout.alignment: Qt.AlignHCenter
            visible: !hideButtons

            ButtonBase {
                id: okButton
                text: qsTr("OK")
                visible: (StandardButton.Ok & standardButtons) === StandardButton.Ok
                isDefault: activeFocus || activeFocusItem && activeFocusItem.objectName !== "ButtonBase"
                onClicked: {
                    root.accepted()
                    if (!stayOnScreen) {
                        root.destroy()
                    } else {
                        stayOnScreen = false
                    }
                }
            }

            ButtonBase {
                text: qsTr("Cancel")
                visible: (StandardButton.Cancel & standardButtons) === StandardButton.Cancel
                onClicked: {
                    root.rejected()
                    root.destroy()
                }
            }

            ButtonBase {
                text: qsTr("Close")
                visible: (StandardButton.Close & standardButtons) === StandardButton.Close
                onClicked: {
                    root.rejected()
                    root.destroy()
                }
            }
        }
    }
}
