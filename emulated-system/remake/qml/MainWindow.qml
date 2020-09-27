import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Controls 2.14
import "qrc:/crane"

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
        x: 503
        y: 57
        z: 1000
    }

    CarBody {
        id: carBody

        bodyType: CarBody.TypeOne
        x: 531
        y: 267

        Connections {
            target: crane
            onGrappleOpenChanged: {
                if (crane.grappleOpen) {
                    crane.tryRelease(carBody)
                } else {
                    crane.tryCatch(carBody)
                }
            }
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
            crane.grappleOpen ^= 1
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

    Rectangle {
        x: 100
        y: 300
        width: 50
        height: 50
        color: "#000000"

        property int timeUnit: 10

        function animate(destination) {
            var duration = Math.abs(destination - x) * timeUnit

            animation.stop()
            animation.to = destination
            animation.duration = duration
            animation.start()
        }

        function stop() {
            animation.stop()
        }

        NumberAnimation on x {
            id: animation
        }

        id: dummy
    }

    Button {
        x: 10
        y: 400
        text: "Start"
        onClicked: dummy.animate(300)
    }

    Button {
        x: 200
        y: 400
        text: "Stop"
        onClicked: dummy.stop()
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:600;width:800}
}
##^##*/

