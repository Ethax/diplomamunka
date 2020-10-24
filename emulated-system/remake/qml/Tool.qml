import QtQuick 2.14

Item {
    id: tool

    property Item base: parent
    property int robotType: RobotType.Painter
    property bool active: false

    implicitHeight: displayedAnimation.height
    implicitWidth: displayedAnimation.width

    anchors {
        verticalCenter: base.top
        horizontalCenter: base.horizontalCenter
    }

    AnimatedSprite {
        id: displayedAnimation

        frameCount: 4
        frameDuration: 100
        visible: active

        source: {
            switch (robotType) {
            case RobotType.Painter:
                return "qrc:/robot/Painting.png"
            case RobotType.Welder:
                return "qrc:/robot/Welding.png"
            default:
                console.exception("Invalid robot type:", robotType)
            }
        }

        onVisibleChanged: {
            if (visible) {
                paused = !paused
                paused = !paused
            }
        }
    }
}