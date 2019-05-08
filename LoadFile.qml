import QtQuick 2.7
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.0

import QtQuick.Controls.Styles 1.4

GridLayout {
    id: fileLoadGrid
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
        id: escButton
        implicitHeight: buttonM_h
        implicitWidth: parent.width
        StyledText{
            text: qsTr("esc")
        }
        onClicked: {
            exManager.visible = true
            loadFileManager.visible = false
        }
        Layout.columnSpan: 1
        Layout.rowSpan: 1
        Layout.row: 1
        Layout.column: 1
    }
    Button{
        id: loadFromFileButton
        implicitHeight: buttonM_h
        implicitWidth: parent.width
        StyledText{
            text: qsTr("Load")
        }
        onClicked: {
            //stdTerminal.visible = true
            //stdTerminalButton.visible = false
        }
        Layout.columnSpan: 1
        Layout.rowSpan: 1
        Layout.row: 2
        Layout.column: 1
    }
}
