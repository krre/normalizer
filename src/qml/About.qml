import QtQuick 2.5
import QtQuick.Dialogs 1.2
import "components/messagedialog"

MessageDialogBase {
    title: qsTr("About Greenery")
    standardButtons: StandardButton.Ok
    text: String("<h3>Greenery %1</h3><br>
          Build date: %2<br>
          Copyright (c) 2015, Vladimir Zarypov").arg(mainRoot.version).arg(UTILS.buildDate)
}
