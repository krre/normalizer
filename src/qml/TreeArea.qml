import QtQuick 2.5
import QtCanvas3D 1.0

Canvas3D {
    id: root
    property bool isCurrentTab: mainRoot.currentTab === root
}

