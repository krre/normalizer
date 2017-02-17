import QtQuick 2.8
import QOsg 0.1 as QOsg

QOsg.PositionAttitudeTransform {
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

    QOsg.PositionAttitudeTransform {
        id: pickForm

        QOsg.Geode {
            id: geode

            QOsg.ShapeDrawable {
                id: shapeDrawable
                color: isCurrent ? selectColor : root.color
                shape: QOsg.Box {
                    halfLengths: Qt.vector3d(0.02, 0.02, 0.02)
                }
            }
        }
    }

    QOsg.Geode {
        QOsg.Text3D {
            position: Qt.vector3d(0.03, -0.01, 0)
            color: isCurrent ? selectColor : root.color
            characterSize: 0.015
            characterDepth: 0
            text: arg
        }
    }
}
