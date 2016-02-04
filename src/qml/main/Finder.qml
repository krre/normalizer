import QtQuick 2.6
import QtQuick.Controls 1.5
import QtQuick.Layouts 1.3

ColumnLayout {
    id: root
    width: 200
    height: 200
    spacing: 0
    visible: false

    onVisibleChanged: {
        if (visible) {
            finderTextField.forceActiveFocus()
        } else {
            finderTextField.text = ""
            currentTab.forceActiveFocus()
        }
    }

    TextField {
        id: finderTextField
        Layout.preferredWidth: parent.width
        onTextChanged: operatorProxyModel.setFilterPattern(text)

        Keys.onReturnPressed: root.visible = false
    }

    TableView {
        Layout.preferredWidth: parent.width
        Layout.fillHeight: true
        alternatingRowColors: false
        headerVisible: false
        model: operatorProxyModel

        TableViewColumn {
            role: "name"
            width: 145
        }

        TableViewColumn {
            role: "shortcut"
            width: 50
        }
    }
}
