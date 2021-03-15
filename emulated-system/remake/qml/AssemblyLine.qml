import QtQuick 2.14
import QtQuick.Controls.Styles 1.4
import QtQuick.Extras 1.4
import QtQuick.Controls 1.4

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

        result |= (conveyorBelt.lastBodyType & 3) << 0
        result |= (conveyorBelt.detectedEntries & 7) << 2
        result |= (conveyorBelt.detectedArrivals & 7) << 5

        result |= (operator.motion ? 1 : 0) << 8
        result |= (welderOne.completed ? 1 : 0) << 9
        result |= (welderTwo.completed ? 1 : 0) << 10
        result |= (painterOne.completed && painterTwo.completed ? 1 : 0) << 11
        result |= (factoryReset.checked ? 1 : 0) << 12
        result |= (acknowledge.checked ? 1 : 0) << 13
        result |= (emergencyStop.checked ? 1 : 0) << 14

        return result
    }

    implicitHeight: 515
    implicitWidth: 1024

    Row {
        id: userControls

        x: 342
        y: 418
        spacing: 10

        UserButton {
            id: factoryReset

            text: qsTr("Reset")
            activeColor: "#0040ff"
            activeShadowColor: "#668cff"

            anchors.verticalCenter: parent.verticalCenter
        }

        UserButton {
            id: emergencyStop

            text: qsTr("Stop")
            checkable: true

            anchors.verticalCenter: parent.verticalCenter
        }

        UserButton {
            id: acknowledge

            text: qsTr("Nyugta")
            activeColor: "#00ff00"
            activeShadowColor: "#66ff66"

            anchors.verticalCenter: parent.verticalCenter
        }

        OperationSelector {
            id: operation

            anchors.verticalCenter: parent.verticalCenter
        }
    }

    ConveyorBelt {
        id: conveyorBelt

        x: 77
        y: 202
        activeBelts: (input >> 9) & 7
        beltCount: 3
    }

    Repeater {
        id: destinations

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

        operation: operation.selection
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
        id: robotController

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
}
