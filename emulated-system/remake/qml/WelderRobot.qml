import QtQuick 2.14

Item {
    id: robot

    property bool accelerated: true
    property bool suspended: false

    implicitHeight: robotArm.height
    implicitWidth: robotBase.width

    Image {
        id: robotBase
        anchors.centerIn: robot
        source: "qrc:/robot/PainterBase.png"
    }

    RobotArm {
        id: robotArm
        base: robotBase
        armType: RobotArm.Painter

        onPositionChanged: tempPosition = position
    }

    state: "0"

    property string tempState
    property int tempPosition

    onSuspendedChanged: {
        if (state === "pause") {
            state = tempState
        } else {
            tempState = state
            state = "pause"
        }
    }

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
            name: "pause"

            PropertyChanges {
                target: robotArm
                position: tempPosition
            }
        }
    ]

    transitions: [
        Transition {
            SmoothedAnimation {
                properties: "rotation, position"
                velocity: accelerated ? 20 : 10
            }
        }
    ]
}

/*##^##
Designer {
    D{i:0;autoSize:true;formeditorZoom:1.75;height:480;width:640}
}
##^##*/

