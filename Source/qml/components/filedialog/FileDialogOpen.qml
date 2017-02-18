import QtQuick 2.8

FileDialogBase {
    title: qsTr("Choose SproutB File")
        nameFilters: [ qsTr("SproutB Files (*.sproutb)"), qsTr("All files (*)") ]
}
