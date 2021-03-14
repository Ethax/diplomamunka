import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Controls 2.14
import "qrc:/body"
import "qrc:/crane"
import "qrc:/common"
import "qrc:/conveyor"
import "qrc:/robot"
import "qrc:/operator"

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

    Column {
        ProjectTitle {
            id: projectTitle

            title: "Karosszéria gyártósor"
            author: "Miklós Árpád"
        }

        AssemblyLine {
            id: assemblyLine
        }
    }

    //    Row {
    //        id: beltControls

    //        x: 10
    //        y: 600
    //        spacing: 10

    //        Button {
    //            text: qsTr("Remove")
    //            onClicked: {
    //                conveyorBelt.tryLeave(carBody1)
    //                conveyorBelt.tryLeave(carBody2)
    //            }
    //        }

    //        Button {
    //            text: qsTr("Place")
    //            onClicked: {
    //                conveyorBelt.tryConvey(carBody1)
    //                conveyorBelt.tryConvey(carBody2)
    //            }
    //        }

    //        Button {
    //            text: qsTr("Start/Stop")
    //            onClicked: conveyorBelt.activeBelts ^= 7
    //        }

    //        Button {
    //            text: qsTr("Change State")
    //            onClicked: robotController.position++
    //        }

    //        Button {
    //            text: qsTr("Change Speed")
    //            onClicked: robotController.accelerated ^= 1
    //        }

    //        Button {
    //            text: qsTr("Pause/Resume")
    //            onClicked: robotController.suspended ^= 1
    //        }

    //        Button {
    //            text: qsTr("Enable")
    //            onDownChanged: robotController.enabled = down
    //        }
    //    }

    //    Column {
    //        id: craneControls

    //        spacing: 10

    //        x: 10
    //        y: beltControls.y + beltControls.height + 10

    //        Button {
    //            text: qsTr("Observe")
    //            onClicked: operator.state = Operation.Observation
    //        }

    //        Button {
    //            text: qsTr("Inspect")
    //            onClicked: operator.state = Operation.Inspection
    //        }

    //        Button {
    //            text: qsTr("Correct")
    //            onClicked: operator.state = Operation.Correction
    //        }

    //        Button {
    //            text: qsTr("Destination 5")
    //            onClicked: crane.position = 5
    //        }

    //        Button {
    //            text: qsTr("Destination 3")
    //            onClicked: crane.position = 3
    //        }

    //        Button {
    //            text: qsTr("Destination 1")
    //            onClicked: crane.position = 1
    //        }

    //        Button {
    //            text: qsTr("Destination 7")
    //            onClicked: crane.position = 7
    //        }
    //    }
    Repeater {
        id: carBodies

        model: [BodyType.One, BodyType.Two, BodyType.Three]

        CarBody {
            id: carBody

            bodyType: modelData
            visible: false

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

    //    Button {
    //        x: 676
    //        y: 507
    //        text: qsTr("Move bridge")

    //        onClicked: {
    //            crane.position ^= 1
    //        }
    //    }

    //    Button {
    //        x: 536
    //        y: 507
    //        text: qsTr("Open/Close")

    //        onClicked: {
    //            crane.grappleOpen ^= 1
    //        }
    //    }

    //    CarBody {
    //        id: carBody1

    //        bodyType: BodyType.One
    //        x: conveyorBelt.x - carBody1.width / 2
    //        y: Math.abs(conveyorBelt.height / 2 - height / 2) + conveyorBelt.y

    //        Connections {
    //            target: crane
    //            onGrappleOpenChanged: {
    //                if (crane.grappleOpen) {
    //                    crane.tryRelease(carBody1)
    //                } else {
    //                    crane.tryCatch(carBody1)
    //                }
    //            }
    //        }
    //    }

    //    CarBody {
    //        id: carBody2

    //        bodyType: BodyType.Three
    //        x: conveyorBelt.x + 10 + carBody2.width / 2
    //        y: Math.abs(conveyorBelt.height / 2 - height / 2) + conveyorBelt.y

    //        Connections {
    //            target: crane
    //            onGrappleOpenChanged: {
    //                if (crane.grappleOpen) {
    //                    crane.tryRelease(carBody2)
    //                } else {
    //                    crane.tryCatch(carBody2)
    //                }
    //            }
    //        }
    //    }
}
