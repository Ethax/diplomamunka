import QtQuick 2.14

Item {
    id: lowerArm

    property Item base: parent
    property int robotType: RobotType.Painter
    property real position: 0.0

    readonly property int armLenght: Math.round(height * 0.875)
    readonly property int elbowLength: height - armLenght

    implicitHeight: displayedImage.height
    implicitWidth: displayedImage.width

    anchors {
        top: base.top
        topMargin: Math.round(position)
    }

    Image {
        id: displayedImage

        source: {
            switch (robotType) {
            case RobotType.Painter:
                return "qrc:/robot/PainterArm.png"
            case RobotType.Welder:
                return "qrc:/robot/WelderArm.png"
            default:
                console.exception("Invalid robot type:", robotType)
            }
        }
    }
}