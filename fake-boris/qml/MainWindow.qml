import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.3
import QtQuick.Extras 1.4

Window {
    id: window
    title: qsTr("Boris I/O Controller")
    minimumWidth: 480
    minimumHeight: 640
    color: "#cccccc"
    visible: true

    ColumnLayout {
        anchors.rightMargin: 20
        anchors.leftMargin: 20
        anchors.bottomMargin: 10
        anchors.topMargin: 10
        anchors.fill: parent

        RowLayout {
            spacing: 10
            Layout.fillWidth: true

            Text {
                text: qsTr("INPUT (ACTUATORS)")
                Layout.fillWidth: true
                horizontalAlignment: Text.AlignRight
            }

            Text {
                text: qsTr("OUTPUT (SENSORS)")
                Layout.fillWidth: true
                horizontalAlignment: Text.AlignLeft
            }
        }

        Repeater {
            model: 2

            ColumnLayout {
                property int blockIndex: index

                Repeater {
                    model: 8

                    RowLayout {
                        property int bitIndex: 8 * blockIndex + index
                        property int labelIndex: 10 * blockIndex + index

                        Layout.fillWidth: true

                        CheckButton {
                            id: lowerInput
                            checkable: false
                            checked: boris ? (boris.input >> bitIndex) & 1 : false

                            onCheckedChanged: {
                                checkable = false
                            }
                        }

                        StatusIndicator {
                            color: "#00c000"
                            active: lowerInput.checked
                        }

                        FramedLabel {
                            text: "I" + labelIndex
                        }

                        Rectangle {
                            color: "#999999"
                            height: 20
                            Layout.fillWidth: true
                        }

                        Rectangle {
                            color: "#999999"
                            height: 20
                            Layout.fillWidth: true
                        }

                        FramedLabel {
                            text: "Q" + labelIndex
                        }

                        StatusIndicator {
                            color: "#00c000"
                            active: lowerOutput.checked
                        }

                        CheckButton {
                            id: lowerOutput

                            onCheckedChanged: {
                                if (checked) {
                                    boris.output |= (1 << bitIndex)
                                }
                                else {
                                    boris.output &= ~(1 << bitIndex)
                                }
                            }
                        }
                    }
                }
            }
        }

        PortControllerRow {
            id: portController

            onActivated: active = boris.start()
            onDeactivated: if(boris.isActive()) boris.stop()
            onDroppedDown: portNames = boris.getPortNames()
            Component.onCompleted: portNames = boris.getPortNames()

            Binding {
                target: boris
                property: "portName"
                value: portController.currentPort
            }

            Connections {
                target: boris
                onErrorOccurred: portController.showError(message)
            }
        }
    }
}
