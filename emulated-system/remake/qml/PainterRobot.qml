import QtQuick 2.14

Item {
    id: painterRobot

    property alias accelerated: painterArm.accelerated
    property alias suspended: painterArm.paused
    property alias position: painterArm.position

    implicitHeight: painterArm.height
    implicitWidth: robotBase.width

    Image {
        id: robotBase

        source: "qrc:/robot/PainterBase.png"
        anchors.verticalCenter: painterRobot.verticalCenter
    }

    PainterArm {
        id: painterArm

        base: robotBase
    }
}
