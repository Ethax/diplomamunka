import QtQuick 2.14

Item {
    id: painterRobot

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

        readonly property real homePosition: 0.0
        readonly property real firstPosition: painterArm.thirdPosition / 3.0
        readonly property real secondPosition: 2.0 * painterArm.thirdPosition / 3.0
        readonly property real thirdPosition: robotBase.width - painterArm.width

        robotType: RobotType.Painter

        anchors {
            left: robotBase.left
            leftMargin: Math.round(painterArm.distance)
        }

        states: [
            State {
                name: "0"

                PropertyChanges {
                    target: painterArm
                    lowering: lowered
                    distance: homePosition
                }
            },
            State {
                name: "1"

                PropertyChanges {
                    target: painterArm
                    lowering: raised
                    distance: firstPosition
                }
            },
            State {
                name: "2"

                PropertyChanges {
                    target: painterArm
                    lowering: raised
                    distance: secondPosition
                }
            },
            State {
                name: "3"

                PropertyChanges {
                    target: painterArm
                    lowering: raised
                    distance: thirdPosition
                }
            },
            State {
                name: "4"

                PropertyChanges {
                    target: painterArm
                    lowering: lowered
                    distance: firstPosition
                }
            },
            State {
                name: "5"

                PropertyChanges {
                    target: painterArm
                    lowering: lowered
                    distance: secondPosition
                }
            },
            State {
                name: "6"

                PropertyChanges {
                    target: painterArm
                    lowering: lowered
                    distance: thirdPosition
                }
            }
        ]
    }
}
