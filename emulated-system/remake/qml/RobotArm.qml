import QtQuick 2.14

Item {
    id: robotArm

    enum ArmType {
        Welder,
        Painter
    }

    property Item base: parent
    property int armType: RobotArm.Welder
    property alias toolActive: toolAnimation.visible
    property real position: 0.0

    implicitHeight: lowerArm.armLenght * 2
    implicitWidth: lowerArm.width

    anchors {
        centerIn: base
    }

    Rectangle {
        id: upperArm

        width: Math.round(lowerArm.width * 0.6)
        color: "black"

        anchors {
            horizontalCenter: lowerArm.horizontalCenter
            top: robotArm.verticalCenter
            topMargin: -Math.round(lowerArm.elbowLength / 2)
            bottom: lowerArm.bottom
            bottomMargin: Math.round(lowerArm.elbowLength / 2)
        }
    }

    Image {
        id: lowerArm

        readonly property int armLenght: Math.round(height * 0.875)
        readonly property int elbowLength: height - armLenght

        anchors {
            top: robotArm.top
            topMargin: Math.round(position)
        }

        source: {
            switch (armType) {
            case RobotArm.Welder:
                return "qrc:/robot/WelderArm.png"
            case RobotArm.Painter:
                return "qrc:/robot/PainterArm.png"
            default:
                console.exception("Invalid body type:", bodyType)
            }
        }
    }

    AnimatedSprite {
        id: toolAnimation

        frameCount: 4
        frameDuration: 100

        anchors {
            verticalCenter: lowerArm.top
            horizontalCenter: lowerArm.horizontalCenter
        }

        source: {
            switch (armType) {
            case RobotArm.Welder:
                return "qrc:/robot/Welding.png"
            case RobotArm.Painter:
                return "qrc:/robot/Painting.png"
            default:
                console.exception("Invalid body type:", bodyType)
            }
        }
    }
}
