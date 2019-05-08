import QtQuick 2.7
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.0

import QtQuick.Controls.Styles 1.4
import OpenGLUnderQML 1.0

GridLayout {
    id: managerGrid
    width: parent.width

    property int buttonM_h: {
        if (Qt.platform.os == "android")
            100
        if(Qt.platform.os == "windows")
            30
    }
    property int nbRow: 6
    height: buttonM_h*nbRow
    rows: nbRow
    columns: 1
    property int curRow: 0

    Button{
        id: connectButton
        implicitHeight: buttonM_h
        implicitWidth: parent.width
        StyledText{
            text: qsTr("Connect")
        }
        onClicked: {
            if(Qt.platform.os == "android"){
                basis.startDiscover()
            }
            if(Qt.platform.os == "windows"){
                managerGrid.visible = false
                connectComPort.visible = true
            }
        }
        Layout.columnSpan: 1
        Layout.rowSpan: 1
        Layout.row: 1
        Layout.column: 1
    }

    Button{
        id: stdTerminalButton
        implicitHeight: buttonM_h
        implicitWidth: parent.width
        StyledText{
            text: qsTr("Std. Terminal")
        }
        onClicked: {
            stdTerminal.visible = true
            managerGrid.visible = false
        }

        Layout.columnSpan: 1
        Layout.rowSpan: 1
        Layout.row: 2
        Layout.column: 1
    }
    Button{
        id: loadFileButton
        implicitHeight: buttonM_h
        implicitWidth: parent.width
        StyledText{
            text: qsTr("Load from file")
        }
        onClicked: {
            managerGrid.visible = false
            loadFileManager.visible = true
        }
        Layout.columnSpan: 1
        Layout.rowSpan: 1
        Layout.row: 3
        Layout.column: 1
    }
    Button{
        id: loadLevelerButton
        implicitHeight: buttonM_h
        implicitWidth: parent.width
        StyledText{
            text: qsTr("Leveler")
        }
        onClicked: {
            levelerTerminal.visible = false
            loadFileManager.visible = true
            /* Настраиваем ядро для удобной работы */
            basis.setSendingCmd()
        }
        Layout.columnSpan: 1
        Layout.rowSpan: 1
        Layout.row: 4
        Layout.column: 1
        action: enabled = false

        background: Rectangle {
            implicitHeight: parent.height
            implicitWidth: parent.width
            opacity: enabled ? 1 : 0.3
            border.color: control.down ? "#17a81a" : "#21be2b"
            border.width: 1
            radius: 2
        }

    }
    Button{
        id: testButton
        implicitHeight: buttonM_h
        implicitWidth: parent.width
        StyledText{
            text: qsTr("Add axes")
        }
        onClicked: {
            plot3dogl.setAxes()
        }
        Layout.columnSpan: 1
        Layout.rowSpan: 1
        Layout.row: 5
        Layout.column: 1
    }
}
