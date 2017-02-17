import QtQuick 2.8
import QtQuick.Controls 1.5
import QtQuick.Window 2.2

ApplicationWindow {
    id: mainRoot
    title: Qt.application.name
    visible: true
    width: 800
    height: 600

    SystemPalette {
        id: sysPalette
        colorGroup: SystemPalette.Active
    }
}
