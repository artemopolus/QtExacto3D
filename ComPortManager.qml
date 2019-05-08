import QtQuick 2.7
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.0

import QtQuick.Controls.Styles 1.4


import QMLstyle 1.0

GridLayout{
        id: grid


        width: parent.width
        property int button_h: {
            if (Qt.platform.os == "android")
                100
            if(Qt.platform.os == "windows")
                30
        }
        property int font_s: {
            if (Qt.platform.os == "android")
                48
            if(Qt.platform.os == "windows")
                12
        }
        height: button_h*5

        rows: 4
        columns: 1
        Button{
            implicitHeight: button_h
            implicitWidth: parent.width
            StyledText{
                text: qsTr("Connect to ComPort")
            }
            Layout.columnSpan: 1
            Layout.rowSpan: 1
            Layout.row: 1
            Layout.column: 1
            onClicked: {
                basis.setNewBaudRate(baudrateList.currentText)
                basis.connectComPort(comportList.currentText)
                stdTerminal.visible = true
                grid.visible = false
            }
        }
        CmdList{
            id: comportList
            model: comportModel
            Layout.columnSpan: 1
            Layout.rowSpan: 1
            Layout.row: 2
            Layout.column: 1
        }
        CmdList{
            id: baudrateList
            model: baudrateModel
            Layout.columnSpan: 1
            Layout.rowSpan: 1
            Layout.row: 3
            Layout.column: 1
        }

        Button{
            id: escButton
            implicitHeight: button_h
            implicitWidth: parent.width
            StyledText{
                text: qsTr("esc")
            }
            onClicked: {
                exManager.visible = true
                grid.visible = false
            }
            Layout.columnSpan: 1
            Layout.rowSpan: 1
            Layout.row: 4
            Layout.column: 1
        }
}
