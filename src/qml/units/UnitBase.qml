import QtQuick 2.5
import OsgBridge 1.0 as Osg

Osg.PositionAttitudeTransform {
    id: root
    default property alias shape: shapeDrawable.shape
    property alias pickForm: pickForm
    property alias geode: geode
    property string title
    property string type
    property string arg
    property string unitId
    property bool isCurrent: geode.name === currentGeode
    property color color: "yellow"
    property color selectColor: "white"
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
                    halfLengths: Qt.vector3d(0.02, 0.02, 0.02)
                }
            }
        }
    }

    Osg.Geode {
        Osg.Text3D {
            position: Qt.vector3d(0.03, -0.01, 0)
            color: isCurrent ? selectColor : root.color
            characterSize: 0.015
            characterDepth: 0
            text: arg
        }
    }
}
