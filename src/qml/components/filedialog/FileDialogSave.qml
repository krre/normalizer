import QtQuick 2.5
import "../../../js/utils.js" as Utils

FileDialogBase {
    title: qsTr("Save File")
    selectExisting: false
    onAccepted: {
        var path = UTILS.urlToPath(fileUrl)
        currentTab.filePath = path
        tabView.getTab(tabView.currentIndex).title = UTILS.urlToFileName(path)
        Utils.saveFile(path)
    }
}

