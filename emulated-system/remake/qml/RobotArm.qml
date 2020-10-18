import QtQuick 2.14

Item {
    id: robotArm

    enum ArmType {
        Welder,
        Painter
    }

    property Item base: parent
    property int armType: RobotArm.Welder

    implicitHeight: lowerArm.height * 1.75
    implicitWidth: lowerArm.width

    anchors {
        centerIn: base
    }

    Rectangle {
        id: upperArm

        height: lowerArm.height / 7 + lowerArm.anchors.topMargin
        width: lowerArm.width * 0.6

        color: "black"

        anchors {
            horizontalCenter: robotArm.horizontalCenter
            top: robotArm.verticalCenter
            topMargin: -lowerArm.height / 14
        }
    }

    Image {
        id: lowerArm

        anchors {
            top: robotArm.top
            topMargin: 30
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
