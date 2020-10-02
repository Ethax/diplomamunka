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

    ConveyorBelt {
        id: conveyorBelt2
        x: conveyorBelt.x + conveyorBelt.width
        y: 10
    }

    ConveyorBelt {
        id: conveyorBelt
        x: 10
        y: 10
        nextSegment: conveyorBelt2
    }

    CarBody {
        id: carBody2
        x: 10
        y: 20

        bodyType: CarBody.TypeTwo
    }

    Button {
        x: 10
        y: 100
        text: qsTr("Convey/Stop")

        onClicked: {
            conveyorBelt.running ^= 1
            conveyorBelt2.running ^= 1
        }
    }

    Button {
        x: 20 + width
        y: 100
        text: qsTr("Place On")

        onClicked: conveyorBelt.tryPlaceOn(carBody2)
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

    Row {
        spacing: 5

        Repeater {
            id: repeater
            model: 3

            Rectangle {
                id: rectangle

                property Rectangle next
                property alias text: text.text

                function hasNext() {
                    return next !== null
                }

                height: 20
                width: 100
                color: "red"
                y: 350

                Component.onCompleted: {
                    if (index > 0) {
                        repeater.itemAt(index - 1).next = this
                    }
                }

                Text {
                    id: text
                    text: "[" + index + "]"
                    anchors.centerIn: parent
                }
            }
        }

        Component.onCompleted: {
            for (var i = 0; i < repeater.count; ++i) {
                var item = repeater.itemAt(i)
                if (item.hasNext()) {
                    item.text += " -> " + item.next.text
                }
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:600;width:800}
}
##^##*/

