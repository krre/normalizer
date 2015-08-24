import QtQuick 2.5
import Qt3D 2.0
import Qt3D.Renderer 2.0
import "../../js/utils.js" as Utils

Entity {
    id: root
    property string text
    property int y: 1
    property real scale: 5
    property string setOfLetters: "abcdefghijklmnoprstuvwxyz0123456789 "

    onTextChanged: {
        // remove old letters
        for (var item in root.childNodes) {
            var child = root.childNodes[item]
            if (child) {
                child.destroy()
            }
        }

        for (var index in text) {
            var letter = setOfLetters.search(text[index]) !== -1 ? text[index] : "query"
            if (letter !== " ") {
                textMesh.createObject(root, { x: -index, scale: 5, letter: letter })
            }
        }
    }

    Component {
        id: textMesh
        EntityBase {
            property string letter: "a"
            mesh: Mesh {
                source: "qrc:/assets/obj/letter/" + letter + ".obj"
            }
        }
    }
}


