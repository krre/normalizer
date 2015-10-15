import QtQuick 2.5
import OsgBridge 1.0 as Osg

Osg.PositionAttitudeTransform {
    id: root
    default property alias shape: shapeDrawable.shape
    property alias pickForm: pickForm
    property string title
    property string type
    property string arg
    property string unitId
    property bool isCurrent: geode.name === currentGeode
    property color color: "yellow"
    property color selectColor: "white"
    signal edit(var name)
    objectName: type + unitId

    onIsCurrentChanged: {
        if (isCurrent) {
            currentUnit = root
        }
    }

    Osg.PositionAttitudeTransform {
        id: pickForm

        Osg.Geode {
            id: geode

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
