import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2
import "../../js/command.js" as Command

Item {
    width: 200
    property color labelColor: "white"

    Grid {
        anchors.fill: parent
        anchors.margins: 10
        columns: 2
        columnSpacing: 20
        visible: commandState === Command.Ready

        Label {
            text: "a"
            color: labelColor
        }

        Label {
            text: Command.Add
            color: labelColor
        }

        Label {
            text: "e"
            color: labelColor
        }

        Label {
            text: Command.Edit
            color: labelColor
        }

        Label {
            text: "d"
            color: labelColor
        }

        Label {
            text:  Command.Delete
            color: labelColor
        }

        Label {
            text: "g"
            color: labelColor
        }

        Label {
            text: Command.Go
            color: labelColor
        }

        Label {
            text: "i"
            color: labelColor
        }

        Label {
            text: Command.Info
            color: labelColor
        }
    }

    Column {
        anchors.fill: parent
        anchors.margins: 10
        spacing: 10

        Row {
            visible: commandState !== Command.Ready
            spacing: 20

            Label {
                text: qsTr("Mode:")
                color: labelColor
            }

            Label {
                text: commandState
                color: labelColor
            }
        }

        Grid {
            columns: 2
            columnSpacing: 20
            visible: commandState === Command.Add

            Label {
                text: "m"
                color: labelColor
            }

            Label {
                text: qsTr("Module")
                color: labelColor
            }

            Label {
                text: "f"
                color: labelColor
            }

            Label {
                text: qsTr("Function")
                color: labelColor
            }

            Label {
                text: "a"
                color: labelColor
            }

            Label {
                text: qsTr("Argument")
                color: labelColor
            }

            Label {
                text: "p"
                color: labelColor
            }

            Label {
                text: qsTr("Print Line")
                color: labelColor
            }

            Label {
                text: "r"
                color: labelColor
            }

            Label {
                text: qsTr("Read Line")
                color: labelColor
            }
        }

        Grid {
            columns: 2
            columnSpacing: 20
            visible: commandState === Command.Delete

            Label {
                text: "y"
                color: labelColor
            }

            Label {
                text: qsTr("Yes")
                color: labelColor
            }

            Label {
                text: "n"
                color: labelColor
            }

            Label {
                text: qsTr("No")
                color: labelColor
            }
        }
    }
}
