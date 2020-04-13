import QtQuick.Controls 2.13
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2

RowLayout {
    property alias currentPort: portList.currentValue
    property alias portNames: portList.model
    property alias active: mainSwitch.checked

    signal dropDownOpened
    signal activated
    signal deactivated

    function showError(message) {
        errorMessage.text = message
        errorMessage.open()
    }

    Layout.fillWidth: true
    
    ComboBox {
        id: portList
        Layout.fillWidth: true
        enabled: !mainSwitch.checked        
        onPressedChanged: if (pressed) dropDownOpened()
    }
    
    Switch {
        id: mainSwitch
        onCheckedChanged: checked ? activated() : deactivated()
    }

    MessageDialog {
        id: errorMessage
        title: qsTr("Error occurred")
        icon: "Critical"
    }
}
