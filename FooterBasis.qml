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
        height: button_h*7

        rows: 6
        columns: 1
        Button{
            id: connectButton
            implicitHeight: button_h
            implicitWidth: parent.width
            StyledText{
                text: qsTr("Connect")
            }
            Layout.columnSpan: 1
            Layout.rowSpan: 1
            Layout.row: 1
            Layout.column: 1
            onClicked: basis.startDiscover()
        }
        Button{

            implicitHeight: button_h
            implicitWidth: parent.width

            //text: qsTr("Send")
            StyledText{
                text: qsTr("Send")
            }

            Layout.columnSpan: 1
            Layout.rowSpan: 1
            Layout.row: 2
            Layout.column: 1
            onClicked: {
                //basis.setCmdType(CmdList.currentIndex)
                basis.sendCmd2exacto()
            }
        }


        CmdList{
            id: stdCmdList
            //Component.onCompleted: currentIndex = 0
            model: cmdModel
            Layout.columnSpan: 1
            Layout.rowSpan: 1
            Layout.row: 3
            Layout.column: 1
            onCurrentIndexChanged: basis.setCmdType(currentIndex)
        }
        CmdList{
            id: cmdModList
            //Component.onCompleted: currentIndex = 0
            model: ["Command mode", "Hex[00 00 00]", "Ping"]
            Layout.columnSpan: 1
            Layout.rowSpan: 1
            Layout.row: 4
            Layout.column: 1
            onCurrentIndexChanged: {
                if(currentIndex == 0)
                    basis.setCmdType(stdCmdList.currentIndex)
                if(currentIndex == 1)
                    basis.setCmdType(customCommand.text)
            }
        }
//        Button{

//            implicitHeight: button_h
//            implicitWidth: parent.width

//            //text: qsTr("Send")
//            StyledText{
//                text: qsTr("Ping")
//            }

//            Layout.columnSpan: 1
//            Layout.rowSpan: 1
//            Layout.row: 4
//            Layout.column: 1
//            onClicked: {
//                //basis.setCmdType(CmdList.currentIndex)
//                basis.startPinging()
//            }
//        }
        Button{
            id: escButton
            implicitHeight: button_h
            implicitWidth: parent.width
            StyledText{
                text: qsTr("esc")
            }
            onClicked: {
                exManager.visible = true
                stdTerminal.visible = false
            }
            Layout.columnSpan: 1
            Layout.rowSpan: 1
            Layout.row: 6
            Layout.column: 1
        }
        Rectangle{
            id: baseCustomCommand
            color: "white"
            implicitHeight: button_h
            implicitWidth: parent.width
            TextInput{
                id: customCommand
                height:  button_h
                font.pixelSize: font_s
                maximumLength: 8
                anchors.centerIn: parent
                text: "00 00 00"
                onActiveFocusChanged: {
                    selectAll()
                }
                onEditingFinished: {
                    if(cmdModList.currentIndex == 1)
                        basis.setCmdType(text)
                }
            }
            Layout.columnSpan: 1
            Layout.rowSpan: 1
            Layout.row: 5
            Layout.column: 1
        }


}
