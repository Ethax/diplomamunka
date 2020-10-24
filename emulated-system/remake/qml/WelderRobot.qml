import QtQuick 2.14

Item {
    id: robot

    property alias accelerated: robotArm.accelerated
    property alias suspended: robotArm.paused

    implicitHeight: robotArm.height
    implicitWidth: robotBase.width

    state: "0"

    Image {
        id: robotBase
        anchors.centerIn: robot
        source: "qrc:/robot/PainterBase.png"
    }

    RobotArm {
        id: robotArm

        property bool accelerated: true
        readonly property bool completed: transition.stopped && !paused

        robotType: RobotType.Welder
        anchors.centerIn: robotBase
        state: robot.state

        onCompletedChanged: console.log(completed ? "Finished" : "Started")
        onPausedChanged: state = paused ? pause : resume

        states: [
            State {
                name: "0"

                PropertyChanges {
                    target: robotArm
                    position: height / 5.0
                    toolActive: false
                }
            },
            State {
                name: "1"

                PropertyChanges {
                    target: robotArm
                    position: 0
                    toolActive: true
                }
            },
            State {
                name: robotArm.pause

                PropertyChanges {
                    target: robotArm
                    position: position
                    toolActive: toolActive
                }
            }
        ]

        transitions: [
            RobotArmTransition {
                id: transition

                properties: "position"
                useFastAnimation: robotArm.accelerated
            }
        ]
    }
}
