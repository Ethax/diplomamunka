import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.3
import QtQuick.Extras 1.4

Window {
    id: mainWindow
    visible: true
    minimumWidth: 480
    minimumHeight: 640
    color: "#cccccc"
    title: qsTr("Boris I/O Controller")

    ColumnLayout {
        id: applicationLayout
        anchors.rightMargin: 20
        anchors.leftMargin: 20
        anchors.bottomMargin: 10
        anchors.topMargin: 10
        anchors.fill: parent

        RowLayout {
            id: textRow
            enabled: false
            spacing: 10
            Layout.fillWidth: true

            Text {
                id: inputLabel
                text: qsTr("INPUT (ACTUATORS)")
                Layout.fillWidth: true
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignRight
                font.pixelSize: 12
            }

            Text {
                id: outputLabel
                text: qsTr("OUTPUT (SENSORS)")
                Layout.fillWidth: true
                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter
                font.pixelSize: 12
            }
        }

        ColumnLayout {
            id: lsbBlock

            Repeater {
                model: 8

                RowLayout {
                    id: rowLayout
                    width: 100
                    height: 100
                    Layout.fillWidth: true
                    spacing: 5

                    RadioButton {
                        id: radioButton
                        padding: 0
                        spacing: 0
                        autoExclusive: false
                        display: AbstractButton.IconOnly
                    }

                    StatusIndicator {
                        id: statusIndicator
                        color: "#00c000"
                        active: radioButton.checked
                    }

                    Rectangle {
                        id: rectangle
                        width: 200
                        height: 200
                        color: "#00000000"
                        border.width: 1
                        Layout.preferredWidth: 30
                        Layout.preferredHeight: 20
                        Layout.fillWidth: false

                        Text {
                            id: element
                            text: "I" + index
                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment: Text.AlignHCenter
                            anchors.fill: parent
                            font.pixelSize: 12
                        }
                    }

                    Rectangle {
                        id: rectangle1
                        width: 200
                        height: 200
                        color: "#999999"
                        Layout.preferredHeight: 20
                        Layout.preferredWidth: -1
                        Layout.fillWidth: true
                    }

                    Rectangle {
                        id: rectangle2
                        width: 200
                        height: 200
                        color: "#999999"
                        Layout.preferredWidth: -1
                        Layout.preferredHeight: 20
                        Layout.fillWidth: true
                    }

                    Rectangle {
                        id: rectangle3
                        width: 200
                        height: 200
                        border.width: 1
                        color: "#00000000"
                        Layout.preferredWidth: 30

                        Text {
                            id: element1
                            text: "Q" + index
                            font.pixelSize: 12
                            verticalAlignment: Text.AlignVCenter
                            anchors.fill: parent
                            horizontalAlignment: Text.AlignHCenter
                        }

                        Layout.preferredHeight: 20
                        Layout.fillWidth: false
                    }

                    StatusIndicator {
                        id: statusIndicator1
                        color: "#00c000"
                        active: radioButton1.checked
                    }

                    RadioButton {
                        id: radioButton1
                        padding: 0
                        autoExclusive: false
                        display: AbstractButton.IconOnly
                        spacing: 0
                    }

                }
            }
        }

        ColumnLayout {
            id: msbBlock

            Repeater {
                model: 8

                RowLayout {
                    id: rowLayout9
                    width: 100
                    height: 100
                    Layout.fillWidth: true
                    spacing: 5

                    RadioButton {
                        id: radioButton9
                        padding: 0
                        spacing: 0
                        autoExclusive: false
                        display: AbstractButton.IconOnly
                    }

                    StatusIndicator {
                        id: statusIndicator9
                        color: "#00c000"
                        active: radioButton9.checked
                    }

                    Rectangle {
                        id: rectangle9
                        width: 200
                        height: 200
                        color: "#00000000"
                        border.width: 1
                        Layout.preferredWidth: 30
                        Layout.preferredHeight: 20
                        Layout.fillWidth: false

                        Text {
                            id: element9
                            text: "I" + (index + 10)
                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment: Text.AlignHCenter
                            anchors.fill: parent
                            font.pixelSize: 12
                        }
                    }

                    Rectangle {
                        id: rectangle19
                        width: 200
                        height: 200
                        color: "#999999"
                        Layout.preferredHeight: 20
                        Layout.preferredWidth: -1
                        Layout.fillWidth: true
                    }

                    Rectangle {
                        id: rectangle29
                        width: 200
                        height: 200
                        color: "#999999"
                        Layout.preferredWidth: -1
                        Layout.preferredHeight: 20
                        Layout.fillWidth: true
                    }

                    Rectangle {
                        id: rectangle39
                        width: 200
                        height: 200
                        border.width: 1
                        color: "#00000000"
                        Layout.preferredWidth: 30

                        Text {
                            id: element19
                            text: "Q" + (index + 10)
                            font.pixelSize: 12
                            verticalAlignment: Text.AlignVCenter
                            anchors.fill: parent
                            horizontalAlignment: Text.AlignHCenter
                        }

                        Layout.preferredHeight: 20
                        Layout.fillWidth: false
                    }

                    StatusIndicator {
                        id: statusIndicator19
                        color: "#00c000"
                        active: radioButton19.checked
                    }

                    RadioButton {
                        id: radioButton19
                        padding: 0
                        autoExclusive: false
                        display: AbstractButton.IconOnly
                        spacing: 0
                    }

                }
            }
        }

        RowLayout {
            id: controlRow
            Layout.fillWidth: true

            ComboBox {
                id: availablePorts
                enabled: !mainSwitch.checked
                Layout.fillWidth: true
                Component.onCompleted: model = boris.getPortNames()
            }

            Switch {
                id: mainSwitch
            }
        }




    }


}

/*##^##
Designer {
    D{i:0;height:640;width:480}D{i:1;anchors_height:100;anchors_width:100;anchors_x:39;anchors_y:110}
}
##^##*/
