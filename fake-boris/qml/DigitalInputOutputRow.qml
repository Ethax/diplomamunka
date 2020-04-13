import QtQuick 2.12
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.3
import QtQuick.Extras 1.4

RowLayout {
    property alias input: inputButton.checked
    property alias inputCaption: inputLabel.text
    property alias output: outputButton.checked
    property alias outputCaption: outputLabel.text

    property int rowHeight: 20

    Layout.fillWidth: true
    
    CheckButton {
        id: inputButton
        checkable: false
        onCheckedChanged: checkable = false
    }
    
    StatusIndicator {
        color: "#00c000"
        active: inputButton.checked
    }
    
    FramedLabel {
        id: inputLabel
        height: rowHeight
    }
    
    Rectangle {
        color: "#999999"
        height: rowHeight
        Layout.fillWidth: true
    }
    
    Rectangle {
        color: "#999999"
        height: rowHeight
        Layout.fillWidth: true
    }
    
    FramedLabel {
        id: outputLabel
        height: rowHeight
    }
    
    StatusIndicator {
        color: "#00c000"
        active: outputButton.checked
    }
    
    CheckButton {
        id: outputButton
    }
}
