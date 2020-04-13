import QtQuick 2.12
import QtQuick.Layouts 1.3

RowLayout {
    property alias inputCaption: inputColumnText.text
    property alias outputCaption: outputColumnText.text

    spacing: 10
    Layout.fillWidth: true
    
    Text {
        id: inputColumnText
        Layout.fillWidth: true
        horizontalAlignment: Text.AlignRight
    }
    
    Text {
        id: outputColumnText
        Layout.fillWidth: true
        horizontalAlignment: Text.AlignLeft
    }
}
