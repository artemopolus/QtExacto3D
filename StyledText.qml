import QtQuick 2.0
import QMLstyle 1.0

Text {
    //font.pixelSize: MyQMLstyleValues.FontSize
    font.pixelSize: {
        if (Qt.platform.os == "android")
            48
        if(Qt.platform.os == "windows")
            12
    }

    anchors.horizontalCenter: parent.horizontalCenter
    anchors.verticalCenter: parent.verticalCenter
}
