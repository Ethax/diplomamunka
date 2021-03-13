import QtQuick 2.14

Item {
    id: robotArm

    property int robotType: RobotType.Painter

    property bool accelerated: false
    property bool paused: false
    property int position: 0
    property bool toolActive: false
    property bool completed: true

    property real distance: 0.0
    property real lowering: 0.0

    implicitHeight: lowerArm.armLenght * 2
    implicitWidth: lowerArm.width

    state: paused ? "pause" : (position & 7)

    UpperArm {
        id: upperArm

        shoulder: robotArm
        elbow: lowerArm
        offset: lowerArm.elbowLength / 2
    }

    LowerArm {
        id: lowerArm

        base: robotArm
        robotType: robotArm.robotType
        lowering: robotArm.lowering
    }

    Tool {
        id: toolAnimation

        wrist: lowerArm
        robotType: robotArm.robotType
        active: robotArm.toolActive
    }

    transitions: [
        RobotMotionTransition {
            robotArm: robotArm
        },
        RobotPauseTransition {
            robotArm: robotArm
        }
    ]
}
