import QtQuick 2.14
import "qrc:/body"
import "qrc:/conveyor"
import "qrc:/crane"
import "qrc:/operator"
import "qrc:/robot"

Item {
    id: assemblyLine

    property int input: 0

    readonly property int output: {
        var result = 0

        result |= (conveyorBelt.lastBodyType & 3) << 0
        result |= (conveyorBelt.detectedEntries & 7) << 2
        result |= (conveyorBelt.detectedArrivals & 7) << 5

        result |= (operator.motion ? 1 : 0) << 8
        result |= (welderOne.completed ? 1 : 0) << 9
        result |= (welderTwo.completed ? 1 : 0) << 10
        result |= (painterOne.completed && painterTwo.completed ? 1 : 0) << 11
        result |= (operatorControls.factoryResetInitiated ? 1 : 0) << 12
        result |= (operatorControls.acknowledged ? 1 : 0) << 13
        result |= (operatorControls.emergencyStopActive ? 0 : 1) << 14

        return result
    }

    implicitHeight: 515
    implicitWidth: 1024

    ConveyorBelt {
        id: conveyorBelt

        readonly property int beltLength: width / beltCount

        x: 77
        y: 202
        activeBelts: (input >> 9) & 7
        beltCount: 3
    }

    Repeater {
        model: [Qt.point(688, 22), Qt.point(688, 113), Qt.point(688, 296)]

        Destination {
            number: index + 1
            x: modelData.x
            y: modelData.y
        }
    }

    Operator {
        id: operator

        observationX: 619
        observationY: 340

        inspectionX: 619
        inspectionY: 234

        correctionX: 485
        correctionY: 234

        operation: operatorControls.selectedOperation
    }

    OperatorControls {
        id: operatorControls

        x: 342
        y: 418
    }

    Crane {
        id: crane

        x: 683
        y: 0
        z: 1000
        position: (input >> 12) & 7
        grappleOpen: (input >> 15) & 1
    }

    RobotController {
        robotNumber: (input >> 0) & 3
        enabled: (input >> 8) & 1

        accelerated: (input >> 2) & 1
        suspended: (input >> 3) & 1
        position: (input >> 4) & 7
        toolActive: (input >> 7) & 1

        WelderRobot {
            id: welderOne

            number: 1
            x: 195
            y: 68
            rotation: 180
        }

        WelderRobot {
            id: welderTwo

            number: 2
            x: welderOne.x
            y: 256
        }

        PainterRobot {
            id: painterOne

            number: 3
            x: 419
            y: 62
            rotation: 180
        }

        PainterRobot {
            id: painterTwo

            number: painterOne.number
            x: painterOne.x
            y: 266
        }
    }

    SafetyGrid {
        base: conveyorBelt
    }

    Row {
        x: 68

        CarBodyInserter {
            id: bodyOneInserter

            bodyType: BodyType.One
        }

        CarBodyInserter {
            id: bodyTwoInserter

            bodyType: BodyType.Two
        }

        CarBodyInserter {
            id: bodyThreeInserter

            bodyType: BodyType.Three
        }
    }

    Repeater {
        model: [bodyOneInserter, bodyTwoInserter, bodyThreeInserter]

        CarBody {
            id: carBody

            bodyType: modelData.bodyType
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

            Connections {
                target: modelData

                onDestinationSelected: {
                    attachTo(assemblyLine)

                    x = conveyorBelt.x + conveyorBelt.beltLength * destination
                    y = conveyorBelt.y + conveyorBelt.height / 2 - height / 2
                    visible = true

                    conveyorBelt.tryConvey(carBody)
                }
            }
        }
    }
}
