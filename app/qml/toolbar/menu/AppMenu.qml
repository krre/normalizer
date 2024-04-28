import QtQuick
import QtQuick.Controls

Menu {
    transformOrigin: Menu.TopRight

    Component {
        id: aboutDialogComp
        AboutDialog {}
    }

    Action {
        text: qsTr("About %1").arg(app.name)
        onTriggered: aboutDialogComp.createObject(appRoot)
    }
}
