import QtQuick 2.8
import QtQuick.Controls 1.5

TabView {
    property Workspace workspace: count > 0 ? getTab(0).item : null
    tabsVisible: false

    Tab {
        active: true

        Workspace {

        }
    }
}
