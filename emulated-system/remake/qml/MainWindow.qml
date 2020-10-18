import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Controls 2.14
import "qrc:/crane"
import "qrc:/common"
import "qrc:/conveyor"
import "qrc:/robot"

Window {
    id: window

    visible: true
    color: "#dde1e4"
    minimumWidth: 1024
    minimumHeight: 768

    contentItem.transform: Scale {
        xScale: yScale
        yScale: {
            var widthRatio = width / minimumWidth
            var heightRatio = height / minimumHeight

            return Math.min(widthRatio, heightRatio)
        }
    }

    WelderRobot {
        x: 100
        y: 10
    }

    Row {
        id: beltControls

        x: 10
        y: 10
        spacing: 10

        Button {
            text: qsTr("Remove")
            onClicked: conveyorBelt.tryLeave(carBody)
        }

        Button {
            text: qsTr("Place")
            onClicked: conveyorBelt.tryConvey(carBody)
        }

        Button {
            text: qsTr("Start/Stop")
            onClicked: conveyorBelt.activeBelts ^= 7
        }
    }

    Column {
        id: craneControls

        spacing: 10

        x: 10
        y: beltControls.y + beltControls.height + 10

        Button {
            text: qsTr("Destination 5")
            onClicked: crane.position = 5
        }

        Button {
            text: qsTr("Destination 3")
            onClicked: crane.position = 3
        }

        Button {
            text: qsTr("Destination 1")
            onClicked: crane.position = 1
        }

        Button {
            text: qsTr("Destination 7")
            onClicked: crane.position = 7
        }
    }

    SafetyGrid {
        base: conveyorBelt
    }

    ConveyorBelt {
        id: conveyorBelt

        x: 90
        y: 300
        beltCount: 3
    }

    Destination {
        number: 1
        x: 701
        y: 120
    }

    Destination {
        number: 2
        x: 701
        y: 211
    }

    Destination {
        number: 3
        x: 701
        y: 394
    }

    Crane {
        id: crane
        x: 696
        y: 98
        z: 1000
    }

    Button {
        x: 676
        y: 507
        text: qsTr("Move bridge")

        onClicked: {
            crane.position ^= 1
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

    CarBody {
        id: carBody

        bodyType: CarBody.TypeOne
        x: conveyorBelt.x - carBody.width / 2
        y: Math.abs(conveyorBelt.height / 2 - height / 2) + conveyorBelt.y

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
}
