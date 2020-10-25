import QtQuick 2.14

RobotArm {
    id: painterArm

    property Item base: parent
    property bool accelerated: false
    property real distance: 0.0

    readonly property bool completed: transition.stopped && !paused

    robotType: RobotType.Painter

    anchors {
        verticalCenter: base.verticalCenter
        left: base.left
        leftMargin: Math.round(distance)
    }

    onAcceleratedChanged: {
        console.log("Accelerated:", accelerated)
        paused = !paused
        paused = !paused
    }

    states: [
        State {
            name: "0" // HOME

            PropertyChanges {
                target: painterArm
                retraction: height / 5.0
                distance: 0.0
            }
        },
        State {
            name: "4" // Approach point 1

            PropertyChanges {
                target: painterArm
                retraction: 0
                distance: (base.width - width) / 3.0
            }
        },
        State {
            name: "1" // Painting point 1

            PropertyChanges {
                target: painterArm
                retraction: height / 5.0
                distance: (base.width - width) / 3.0
            }
        },

        State {
            name: "5" // Approach point 2

            PropertyChanges {
                target: painterArm
                retraction: 0
                distance: 2.0 * (base.width - width) / 3.0
            }
        },
        State {
            name: "2" // Painting point 2

            PropertyChanges {
                target: painterArm
                retraction: height / 5.0
                distance: 2.0 * (base.width - width) / 3.0
            }
        },
        State {
            name: "6" // Approach point 3

            PropertyChanges {
                target: painterArm
                retraction: 0
                distance: base.width - width
            }
        },
        State {
            name: "3" // Painting point 3

            PropertyChanges {
                target: painterArm
                retraction: height / 5.0
                distance: base.width - width
            }
        },
        State {
            name: "pause"

            PropertyChanges {
                target: painterArm
                retraction: retraction
                distance: distance
            }
        }
    ]

    transitions: [
        RobotArmTransition {
            id: transition

            properties: "retraction, distance"
            useFastAnimation: painterArm.accelerated
        },
        Transition {
            id: pause

            property real remainingTime: 0

            to: "pause"
            reversible: true

            NumberAnimation {
                properties: "retraction, distance"

                duration: {
                    if (state === "pause") {
                        console.log("Pause entered")

                        var desired = painterArm.accelerated ? 500 : 4000
                        var elapsed = Date.now() - transition.startTime

                        pause.remainingTime = Math.max(0, desired - elapsed)
                        return 0
                    } else {
                        console.log("Pause leaved")

                        return Math.round(pause.remainingTime)
                    }
                }
            }
        }
    ]
}
