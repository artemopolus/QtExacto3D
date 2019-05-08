import QtQuick 2.7
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.0

import QtQuick.Controls.Styles 1.4

GridLayout {
    id: levelerGrid
    width: parent.width

    property int buttonM_h: {
        if (Qt.platform.os == "android")
            100
        if(Qt.platform.os == "windows")
            30
    }
    property int nbRow: 2
    height: buttonM_h*nbRow
    rows: nbRow
    columns: 1

    Button{
        id: escLevelerButton
        implicitHeight: buttonM_h
        implicitWidth: parent.width
        StyledText{
            text: qsTr("esc")
        }
        onClicked: {
            exManager.visible = true
            levelerTerminal.visible = false
            /* Возвращаем значения обратно */
            basis.resetSendingCmd()
        }
        Layout.columnSpan: 1
        Layout.rowSpan: 1
        Layout.row: 1
        Layout.column: 1
    }
    Button{
        id: startLevelerButton
        implicitHeight: buttonM_h
        implicitWidth: parent.width
        StyledText{
            text: qsTr("Start")
        }
        onClicked: {
            //stdTerminal.visible = true
            //stdTerminalButton.visible = false
            startLevelerButton.text = qstr("Stop")
            basis.sendCmd2exacto()
        }
        Layout.columnSpan: 1
        Layout.rowSpan: 1
        Layout.row: 2
        Layout.column: 1
    }
}
