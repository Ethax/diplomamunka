import QtQuick 2.14
import QtQuick.Extras 1.4

import "qrc:/body"
import "qrc:/crane"
import "qrc:/common"
import "qrc:/conveyor"
import "qrc:/robot"
import "qrc:/operator"

Item {
    id: assemblyLine

    property int input: 0

    readonly property int output: {
        var result = 0

        result |= conveyorBelt.lastBodyType
        result |= conveyorBelt.detectedEntries << 2
        result |= conveyorBelt.detectedArrivals << 5

        result |= operator.operation << 8
        result |= robotController.completions << 9
        result |= factoryReset.checked << 12
        result |= acknowledge.checked << 13
        result |= emergencyStop.checked << 14

        return result
    }

    ToggleButton {
        id: factoryReset

        text: qsTr("Factory reset")
    }

    ToggleButton {
        id: emergencyStop

        text: qsTr("Emergency stop")
    }

    DelayButton {
        id: acknowledge

        text: qsTr("Acknowledge")
        delay: 0
    }

    Dial {
        id: operation

        readonly property int selection: {
            switch (value) {
            case 0:
                return Operation.Observation
            case 1:
                return Operation.Inspection
            case 2:
                return Operation.Correction
            default:
                throw "Invalid operation value: " + value
            }
        }

        minimumValue: 0
        maximumValue: 2
        stepSize: 1
        tickmarksVisible: true
    }

    ConveyorBelt {
        id: conveyorBelt

        activeBelts: (input >> 9) & 7

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

    Operator {
        id: operator

        observationX: 632
        observationY: 438

        inspectionX: 632
        inspectionY: 332

        correctionX: 498
        correctionY: 332

        state: operation.selection
    }

    Crane {
        id: crane

        position: (input >> 12) & 7
        grappleOpen: (input >> 15) & 1

        x: 696
        y: 98
        z: 1000
    }

    RobotController {
        id: robotController

        readonly property int completions: {
            var result = 0

            result |= welderOne.completed
            result |= welderTwo.completed << 1
            result |= (painterOne.completed && painterTwo.completed) << 2

            return result
        }

        robotNumber: (input >> 0) & 3
        enabled: (input >> 8) & 1

        accelerated: (input >> 2) & 1
        suspended: (input >> 3) & 1
        position: (input >> 4) & 7
        toolActive: (input >> 7) & 1

        WelderRobot {
            id: welderOne

            number: 1
            x: 208
            y: 354
        }

        WelderRobot {
            id: welderTwo

            number: 2
            x: 208
            y: 354
        }

        PainterRobot {
            id: painterOne

            number: 3
            x: 432
            y: 364
        }

        PainterRobot {
            id: painterTwo

            number: 3
            x: 432
            y: 364
        }
    }

    SafetyGrid {
        base: conveyorBelt
    }
}
