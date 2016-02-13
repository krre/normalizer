import QtQuick 2.6
import QtQuick.Controls 1.5
import QtQuick.Layouts 1.3
import "../../js/operators.js" as Operators

ColumnLayout {
    id: root
    anchors.centerIn: parent
    width: 200
    height: 200
    spacing: 0

    Component.onCompleted: finderTextField.forceActiveFocus()

    Action {
        shortcut: "Esc"
        onTriggered: root.destroy()
    }

    TextField {
        id: finderTextField
        Layout.preferredWidth: parent.width
        onTextChanged: OperatorProxyModel.setFilterPattern(text)

        Keys.onReturnPressed: {
            var index = OperatorProxyModel.sourceIndex(tableView.currentRow)
            Operators.operators[index].action()
            root.destroy()
        }
        Keys.onDownPressed: tableView.incrementRow()
        Keys.onUpPressed: tableView.decrementRow()
    }

    TableView {
        id: tableView
        Layout.preferredWidth: parent.width
        Layout.fillHeight: true
        headerVisible: false
        model: OperatorProxyModel

        onRowCountChanged: {
            if (rowCount) {
                selectRow(0)
            }
        }

        function selectRow(row) {
            currentRow = row
            selection.clear()
            selection.select(row)
        }

        function incrementRow() {
            if (currentRow < rowCount - 1) {
                selectRow(currentRow + 1)
            }
        }

        function decrementRow() {
            if (currentRow > 0) {
                selectRow(currentRow - 1)
            }
        }

        TableViewColumn {
            role: "name"
            width: 130
        }

        TableViewColumn {
            role: "shortcut"
            width: 50
        }
    }
}
