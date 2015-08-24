import QtQuick 2.5
import Qt3D 2.0
import Qt3D.Renderer 2.0

Entity {
    id: root
    property string text: "abc"
    property int y: 1
    property real scale: 5

    Component.onCompleted: {
        a.createObject(root, { x: 0, y: y, scale: scale })
        b.createObject(root, { x: -1, y: y, scale: scale })
        c.createObject(root, { x: -2, y: y, scale: scale })
        query.createObject(root, { x: -3, y: y, scale: scale })
    }

    Component {
        id: a
        EntityBase {
            mesh: Mesh {
                source: "qrc:/assets/obj/letter/a.obj"
            }
        }
    }

    Component {
        id: b
        EntityBase {
            mesh: Mesh {
                source: "qrc:/assets/obj/letter/b.obj"
            }
        }
    }

    Component {
        id: c
        EntityBase {
            mesh: Mesh {
                source: "qrc:/assets/obj/letter/c.obj"
            }
        }
    }

    Component {
        id: query
        EntityBase {
            mesh: Mesh {
                source: "qrc:/assets/obj/letter/query.obj"
            }
        }
    }
}


