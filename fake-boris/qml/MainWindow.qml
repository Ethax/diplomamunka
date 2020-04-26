import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.3

Window {
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

        ColumnCaptionRow {
            inputCaption: qsTr("INPUT (ACTUATORS)")
            outputCaption: qsTr("OUTPUT (SENSORS)")
        }

        Repeater {
            model: 2

            ColumnLayout {
                readonly property int blockIndex: index

                Repeater {
                    model: 8

                    DigitalInputOutputRow {
                        id: digitalIO

                        readonly property int bitIndex: 8 * blockIndex + index
                        readonly property int labelIndex: 10 * blockIndex + index

                        inputCaption: qsTr("I") + labelIndex
                        outputCaption: qsTr("Q") + labelIndex

                        onOutputChanged: {
                            if (output) {
                                boris.output |= 1 << bitIndex
                            } else {
                                boris.output &= ~(1 << bitIndex)
                            }
                        }

                        Connections {
                            target: boris
                            onInputChanged: digitalIO.input = (value >> bitIndex) & 1
                        }
                    }
                }
            }
        }

        PortControllerRow {
            id: portController

            Component.onCompleted: portNames = boris.getPortNames()
            onDropDownOpened: portNames = boris.getPortNames()
            onCurrentPortChanged: boris.portName = currentPort

            onActivated: active = boris.start()
            onDeactivated: {
                if (boris.isActive()) {
                    boris.stop()
                }
            }

            Connections {
                target: boris
                onErrorOccurred: portController.showError(message)
            }
        }
    }
}
