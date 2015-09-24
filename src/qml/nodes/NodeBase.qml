import QtQuick 2.5
import osg 2.0 as OSG
import "../../js/command.js" as Command

OSG.PositionAttitudeTransform {
    id: root
    default property alias shape: shapeDrawable.shape
    property string name
    property string arg
    property bool isCurrent: root === currentNode
    property bool isEdit: isCurrent && commandState === Command.Edit
    property string nodeId
    property color color: "yellow"
    signal edit(var name)

    OSG.Geode {

        OSG.ShapeDrawable {
            id: shapeDrawable
            color: isCurrent ? "darkred" : root.color
            shape: OSG.Box {
                halfLengths: Qt.vector3d(0.1, 0.1, 0.1)
            }
        }
    }
}

/*

Rectangle {


    MouseArea {
        anchors.fill: parent
        onClicked: currentNode = root
    }

    ColumnLayout {
        anchors.fill: parent

        Label {
            text: name
            color: "white"
            Layout.alignment: Qt.AlignHCenter
        }

        TextEdit {
            property bool isEscape: false
            visible: isEdit
            Layout.fillWidth: true
            horizontalAlignment: TextEdit.AlignHCenter
            onVisibleChanged: {
                if (visible) {
                    isEscape = false
                    text = arg
                    selectAll()
                    forceActiveFocus()
                } else if (isCurrent && !isEscape) {
                    arg = text
                    edit(text)
                }
            }
            color: "white"

            Keys.onReturnPressed: commandState = Command.Ready
            Keys.onEnterPressed: commandState = Command.Ready
            Keys.onEscapePressed: {
                isEscape = true
                commandState = Command.Ready
            }
        }

        Label {
            Layout.alignment: Qt.AlignHCenter
            text: arg
            color: "white"
            visible: !isEdit
        }
    }
}
*/
