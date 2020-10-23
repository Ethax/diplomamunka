import QtQuick 2.14

Item {
    id: robot

    property alias accelerated: robotArm.accelerated
    property alias suspended: robotArm.suspended

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
        property bool suspended: false
        property string animatedProperties: "position"

        readonly property string pause: "pause"
        readonly property string resume: state !== pause ? state : resume

        armType: RobotArm.Painter
        anchors.centerIn: robotBase

        state: robot.state
        onSuspendedChanged: state = suspended ? pause : resume

        states: [
            State {
                name: "0"

                PropertyChanges {
                    target: robotArm
                    position: robotArm.height / 5.0
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
            Transition {
                SequentialAnimation {
                    ScriptAction {
                        script: console.log("Started")
                    }
                    SmoothedAnimation {
                        properties: robotArm.animatedProperties
                        velocity: robotArm.accelerated ? 20 : 10
                    }
                    ScriptAction {
                        script: {
                            if (robotArm.state === robotArm.pause) {
                                console.log("Paused")
                            } else {
                                console.log("Finished")
                            }
                        }
                    }
                }
            }
        ]
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;formeditorZoom:1.75;height:480;width:640}
}
##^##*/

