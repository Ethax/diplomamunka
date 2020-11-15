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

        Button {
            text: qsTr("Change State")
            onClicked: robot2.position++
        }

        Button {
            text: qsTr("Change Speed")
            onClicked: robot2.accelerated ^= 1
        }

        Button {
            text: qsTr("Pause/Resume")
            onClicked: robot2.suspended ^= 1
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

    Repeater {
        id: destinations

        model: [Qt.point(701, 120), Qt.point(701, 211), Qt.point(701, 394)]

        Destination {
            number: index + 1
            x: modelData.x
            y: modelData.y
        }
    }

    Repeater {
        id: carBodies

        model: [CarBody.TypeOne, CarBody.TypeTwo, CarBody.TypeThree]

        CarBody {
            bodyType: modelData
            visible: false
        }
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

    RobotController {
        id: robotController

        robots: [robot, robot2]

        onCompletedChanged: console.log("Completed", completed)
    }

    PainterRobot {
        id: robot
        x: 432
        y: 364
        position: 0
    }

    WelderRobot {
        id: robot2
        x: 208
        y: 354
        position: 0

        //        Rectangle {
        //            anchors.fill: parent
        //            border.color: "black"
        //            color: "transparent"
        //        }
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
