import QtQuick 2.14

Item {
    id: robotArm

    property int robotType: RobotType.Painter
    property bool paused: false
    property alias position: lowerArm.position
    property alias toolActive: toolAnimation.active

    readonly property string pause: "pause"
    readonly property string resume: state !== pause ? state : resume

    implicitHeight: lowerArm.armLenght * 2
    implicitWidth: lowerArm.width

    UpperArm {
        id: upperArm

        base: robotArm
        joint: lowerArm
        offset: lowerArm.elbowLength / 2.0
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
