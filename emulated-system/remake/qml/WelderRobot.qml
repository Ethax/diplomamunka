import QtQuick 2.14

Item {
    id: welderRobot

    property int number: 0

    property alias accelerated: welderArm.accelerated
    property alias suspended: welderArm.paused
    property alias position: welderArm.position
    property alias toolActive: welderArm.toolActive
    readonly property alias completed: welderArm.completed

    implicitHeight: welderArm.height
    implicitWidth: welderBase.width

    Image {
        id: welderBase

        source: "qrc:/robot/WelderBase.png"

        anchors {
            verticalCenter: welderRobot.verticalCenter
        }
    }

    RobotArm {
        id: welderArm

        readonly property real raised: 0.0
        readonly property real centered: welderArm.height / 15.0
        readonly property real lowered: welderArm.height / 5.0

        readonly property real homePosition: -90.0
        readonly property real firstPosition: -30.0
        readonly property real secondPosition: 0.0
        readonly property real thirdPosition: 30.0

        robotType: RobotType.Welder

        anchors {
            horizontalCenter: welderRobot.horizontalCenter
        }

        states: [
            State {
                name: "0"

                PropertyChanges {
                    target: welderArm
                    lowering: lowered
                    rotation: homePosition
                }
            },
            State {
                name: "1"

                PropertyChanges {
                    target: welderArm
                    lowering: raised
                    rotation: firstPosition
                }
            },
            State {
                name: "2"

                PropertyChanges {
                    target: welderArm
                    lowering: centered
                    rotation: secondPosition
                }
            },
            State {
                name: "3"

                PropertyChanges {
                    target: welderArm
                    lowering: raised
                    rotation: thirdPosition
                }
            },
            State {
                name: "4"

                PropertyChanges {
                    target: welderArm
                    lowering: lowered
                    rotation: firstPosition
                }
            },
            State {
                name: "5"

                PropertyChanges {
                    target: welderArm
                    lowering: lowered
                    rotation: secondPosition
                }
            },
            State {
                name: "6"

                PropertyChanges {
                    target: welderArm
                    lowering: lowered
                    rotation: thirdPosition
                }
            }
        ]
    }
}
