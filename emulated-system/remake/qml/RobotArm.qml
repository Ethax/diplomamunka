import QtQuick 2.14

Item {
    id: robotArm

    property int robotType: RobotType.Painter
    property int position: 0
    property bool paused: false
    property alias toolActive: toolAnimation.active
    property alias retraction: lowerArm.position

    implicitHeight: lowerArm.armLenght * 2
    implicitWidth: lowerArm.width

    state: paused ? "pause" : (position & 7)

    UpperArm {
        id: upperArm

        base: robotArm
        joint: lowerArm
        offset: lowerArm.elbowLength / 2
    }

    LowerArm {
        id: lowerArm

        base: robotArm
        robotType: robotArm.robotType
    }

    Tool {
        id: toolAnimation

        base: lowerArm
        robotType: robotArm.robotType
    }
}
