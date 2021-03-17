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

        readonly property real positionHome: -90.0
        readonly property real positionOne: -30.0
        readonly property real positionTwo: 0.0
        readonly property real positionThree: 30.0

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
                    rotation: positionHome
                }
            },
            State {
                name: "1"

                PropertyChanges {
                    target: welderArm
                    lowering: raised
                    rotation: positionOne
                }
            },
            State {
                name: "2"

                PropertyChanges {
                    target: welderArm
                    lowering: centered
                    rotation: positionTwo
                }
            },
            State {
                name: "3"

                PropertyChanges {
                    target: welderArm
                    lowering: raised
                    rotation: positionThree
                }
            },
            State {
                name: "5"

                PropertyChanges {
                    target: welderArm
                    lowering: lowered
                    rotation: positionOne
                }
            },
            State {
                name: "6"

                PropertyChanges {
                    target: welderArm
                    lowering: lowered
                    rotation: positionTwo
                }
            },
            State {
                name: "7"

                PropertyChanges {
                    target: welderArm
                    lowering: lowered
                    rotation: positionThree
                }
            }
        ]
    }
}
