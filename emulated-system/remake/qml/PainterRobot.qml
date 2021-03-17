import QtQuick 2.14

Item {
    id: painterRobot

    property int number: 0

    property alias accelerated: painterArm.accelerated
    property alias suspended: painterArm.paused
    property alias position: painterArm.position
    property alias toolActive: painterArm.toolActive
    readonly property alias completed: painterArm.completed

    implicitHeight: painterArm.height
    implicitWidth: robotBase.width

    Image {
        id: robotBase

        source: "qrc:/robot/PainterBase.png"

        anchors {
            verticalCenter: painterRobot.verticalCenter
        }
    }

    RobotArm {
        id: painterArm

        readonly property real raised: 0.0
        readonly property real lowered: painterArm.height / 5.0

        readonly property real positionHome: 0.0
        readonly property real positionOne: painterArm.positionThree / 3.0
        readonly property real positionTwo: painterArm.positionThree * 2.0 / 3.0
        readonly property real positionThree: robotBase.width - painterArm.width

        robotType: RobotType.Painter

        anchors {
            left: painterRobot.left
            leftMargin: Math.round(painterArm.distance)
        }

        states: [
            State {
                name: "0"

                PropertyChanges {
                    target: painterArm
                    lowering: lowered
                    distance: positionHome
                }
            },
            State {
                name: "1"

                PropertyChanges {
                    target: painterArm
                    lowering: raised
                    distance: positionOne
                }
            },
            State {
                name: "2"

                PropertyChanges {
                    target: painterArm
                    lowering: raised
                    distance: positionTwo
                }
            },
            State {
                name: "3"

                PropertyChanges {
                    target: painterArm
                    lowering: raised
                    distance: positionThree
                }
            },
            State {
                name: "5"

                PropertyChanges {
                    target: painterArm
                    lowering: lowered
                    distance: positionOne
                }
            },
            State {
                name: "6"

                PropertyChanges {
                    target: painterArm
                    lowering: lowered
                    distance: positionTwo
                }
            },
            State {
                name: "7"

                PropertyChanges {
                    target: painterArm
                    lowering: lowered
                    distance: positionThree
                }
            }
        ]
    }
}
