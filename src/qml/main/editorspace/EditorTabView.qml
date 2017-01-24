import QtQuick 2.8
import QtQuick.Controls 1.5

TabView {
    frameVisible: false

    function nextTab() {
        if (currentIndex + 1 < count) {
            currentIndex++
        } else {
            currentIndex = 0
        }
    }

    function previousTab() {
        if (currentIndex - 1 < 0) {
            currentIndex = count - 1
        } else {
            currentIndex--
        }
    }

    function findTab(path) {
        for (var i = 0; i < count; i++) {
            if (getTab(i).item.path === path) {
                return i
            }
        }

        return -1
    }

    function forEachTab(callback) {
        for (var i = 0; i < count; i++) {
            callback(getTab(i).item)
        }
    }
}
