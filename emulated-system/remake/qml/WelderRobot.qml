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

        armType: RobotArm.Painter
        anchors.centerIn: robotBase
    }

    state: "0"

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
            id: pause

            readonly property alias stateName: pause.name

            property string pausedState: state === stateName ? pausedState : state
            property bool paused: suspended

            onPausedChanged: state = state === name ? pausedState : name

            PropertyChanges {
                target: robotArm
                position: position
                toolActive: toolActive
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

