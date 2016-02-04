import QtQuick 2.6
import "../../../js/utils.js" as Utils

FileDialogBase {
     title: qsTr("Save Sprout file")
     nameFilters: [ qsTr("Sprout (*.sprout)"), qsTr("All files (*)") ]
     selectExisting: false
     onAccepted: Utils.saveAsSprout(Core.urlToPath(fileUrl))
}
