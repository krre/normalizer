import QtQuick 2.5
import OsgBridge 1.0 as Osg
import "../../js/command.js" as Command

Osg.PositionAttitudeTransform {
    id: root
    default property alias shape: shapeDrawable.shape
    property string title
    property string arg
    property bool isCurrent: root === currentNode
    property bool isEdit: isCurrent && commandState === Command.Edit
    property string unitId
    property color color: "yellow"
    property color selectColor: "white"
    signal edit(var name)

    Osg.PositionAttitudeTransform {

        Osg.Geode {

            Osg.ShapeDrawable {
                id: shapeDrawable
                color: isCurrent ? selectColor : root.color
                shape: Osg.Box {
                    halfLengths: Qt.vector3d(0.1, 0.1, 0.1)
                }
            }
        }
    }

    Osg.Geode {

        Osg.Text3D {
            position: Qt.vector3d(-0.1, 0.15, 0)
            color: isCurrent ? selectColor : root.color
            characterSize: 0.1
            characterDepth: 0
            text: title
        }
    }

    Osg.Geode {

        Osg.Text3D {
            position: Qt.vector3d(0.12, 0, 0)
            color: isCurrent ? selectColor : root.color
            characterSize: 0.1
            characterDepth: 0
            text: arg
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
