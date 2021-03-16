import QtQuick 2.14
import QtQuick.Window 2.14

Window {
    id: window

    visible: true
    color: "#dde1e4"
    minimumWidth: 1024
    minimumHeight: 648

    contentItem.transform: Scale {
        xScale: yScale
        yScale: {
            var widthRatio = width / minimumWidth
            var heightRatio = height / minimumHeight

            return Math.min(widthRatio, heightRatio)
        }
    }

    Column {
        spacing: 10

        ProjectTitle {
            id: projectTitle

            title: "Karosszéria gyártósor"
            author: "Miklós Árpád"
        }

        AssemblyLine {
            id: assemblyLine

            Binding {
                target: assemblyLine
                property: "input"
                value: boris ? boris.input : 0
            }

            Binding {
                target: boris
                property: "output"
                value: assemblyLine.output
            }
        }

        PortController {
            id: portController

            debugging: debugPort

            Component.onCompleted: portNames = boris.getPortNames()
            onDropDownOpened: portNames = boris.getPortNames()

            onConnectedChanged: {
                if (connected) {
                    connected = boris.start()
                } else if (boris.isActive()) {
                    boris.stop()
                }
            }

            Binding {
                target: boris
                property: "portName"
                value: portController.selectedPort
            }

            Binding {
                target: debugPort
                when: portController.debugging
                property: "data"
                value: portController.debugData
            }

            Connections {
                target: boris
                onErrorOccurred: portController.showError(message)
            }
        }
    }
}
