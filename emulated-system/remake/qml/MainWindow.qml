import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Controls 2.14

Window {
    id: window

    visible: true
    minimumWidth: 800
    minimumHeight: 600

    contentItem.transform: Scale {
        xScale: yScale
        yScale: {
            var widthRatio = width / minimumWidth
            var heightRatio = height / minimumHeight

            return Math.min(widthRatio, heightRatio)
        }
    }

    Rectangle {
        id: master
        x: 10
        y: 10
        width: 50
        height: 50
        color: "#00ff00"

        Behavior on x {
            NumberAnimation {
                duration: 6000
                easing.type: Easing.InOutCubic

                onRunningChanged: {
                    if (!running) {
                        master.color = "#ff0000"
                    }
                }
            }
        }

        onXChanged: {
            if (carBody.overlaps(sensor)) {
                sensor.color = "#ff0000"
            } else {
                sensor.color = "#ffff00"
            }
        }
    }

    Button {
        id: move
        x: 50
        y: 327
        text: qsTr("Move")

        onClicked: {
            master.x = 400
        }
    }

    Crane {
        id: crane
        x: 563
        y: 54
    }

    CarBody {
        id: carBody
        bodyType: CarBody.TypeOne
        x: 82
        y: 123

        Component.onCompleted: {
            attachTo(master)
        }
    }

    Button {
        x: 676
        y: 507
        text: qsTr("Move crane")

        onClicked: {
            crane.position++
        }
    }

    Button {
        x: 536
        y: 507
        text: qsTr("Open/Close")

        onClicked: {
            crane.gripperOpen ^= 1
        }
    }

    Rectangle {
        id: sensor
        x: 257
        y: 81
        width: 5
        height: 200
        color: "#ffff00"
    }

    Button {
        x: 348
        y: 171
        text: qsTr("Destination 5")
        onClicked: crane.position = 5
    }

    Button {
        x: 348
        y: 228
        text: qsTr("Destination 3")
        onClicked: crane.position = 3
    }

    Button {
        x: 348
        y: 283
        text: qsTr("Destination 1")
        onClicked: crane.position = 1
    }

    Button {
        x: 348
        y: 339
        text: qsTr("Destination 7")
        onClicked: crane.position = 7
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
