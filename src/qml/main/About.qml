import QtQuick 2.6
import "../components/"

MessageDialogBase {
    title: qsTr("About %1".arg(Qt.application.name))
    text: "<h3>%1 %2</h3>
          Based on Qt %3<br>
          Build on %4<br><br>
          <a href=\"https://github.com/krre/greensilage\">
          https://github.com/krre/greensilage</a><br><br>
          Copyright © 2015-2016, Vladimir Zarypov
        ".arg(Qt.application.name).arg(Qt.application.version).arg(Core.qtVersion).arg(Core.buildDate)
}
