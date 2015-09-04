import QtQuick 2.5
import Qt3D 2.0
import Qt3D.Renderer 2.0
import "../../js/utils.js" as Utils

EntityBase {
    id: root
    property string text
    property string setOfLetters: "abcdefghijklmnoprstuvwxyz0123456789 "
    mesh: null
    property var letters: []

    NodeInstantiator {
        model: letters
        delegate: EntityBase {
            x: -index / 1.8
            scale: 2
            mesh: Mesh {
                source: "qrc:/assets/obj/letter/" + letters[index] + ".obj"
            }
        }
    }

    onTextChanged: {
        letters = []
        for (var index in text) {
            var letter = setOfLetters.search(text[index]) !== -1 ? text[index] : "query"
            letters.push(letter)
        }
    }
}


