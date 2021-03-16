import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Dialogs 1.3
import QtQuick.Extras 1.4
import "qrc:/common"

Item {
    id: portController

    property bool debugging: false
    readonly property alias debugData: dataManipulator.data

    property alias connected: mainSwitch.checked
    property alias portNames: portList.model
    property alias selectedPort: portList.currentValue

    signal dropDownOpened

    function showError(message) {
        errorMessage.text = message
        errorMessage.open()
    }

    implicitHeight: portList.height
    implicitWidth: 1024

    HorizontalRepeater {
        id: dataManipulator

        property int data: 0

        itemCount: 16
        spacing: 10
        visible: debugging
        enabled: connected

        anchors {
            left: portController.left
            leftMargin: 10
            verticalCenter: portController.verticalCenter
        }

        StatusIndicator {
            onActiveChanged: {
                var bitMask = 1 << dataManipulator.itemCount - (index + 1)

                if (active) {
                    dataManipulator.data |= bitMask
                } else {
                    dataManipulator.data &= ~bitMask
                }
            }

            onEnabledChanged: {
                if (!enabled) {
                    active = false
                }
            }

            MouseArea {
                anchors.fill: parent
                onClicked: parent.active = !parent.active
            }
        }
    }

    ComboBox {
        id: portList

        enabled: !connected
        palette.button: "#cccccc"

        anchors {
            left: debugging ? dataManipulator.right : portController.left
            leftMargin: 10
            right: mainSwitch.left
            rightMargin: 10
        }

        onPressedChanged: {
            if (pressed) {
                dropDownOpened()
            }
        }
    }

    Switch {
        id: mainSwitch

        palette.midlight: "#cccccc"

        anchors {
            right: portController.right
            rightMargin: 10
        }
    }

    MessageDialog {
        id: errorMessage

        title: qsTr("Hiba történt")
        icon: "Critical"
    }
}
