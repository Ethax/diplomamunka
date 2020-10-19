import QtQuick 2.14

Item {

    id: robot

    Image {
        id: welderBase

        x: 120
        y: 100
        source: "WelderBase.png"
    }

    RobotArm {
        id: robotArm
        base: welderBase
    }

    state: "0"

    states: [
        State {
            name: "0"

            PropertyChanges {
                target: robotArm
                position: robotArm.height / 5.0
                rotation: 0
                toolActive: false
            }
        },
        State {
            name: "1"

            PropertyChanges {
                target: robotArm
                position: 0
                rotation: 45
                toolActive: false
            }
        }
    ]

    transitions: [
        Transition {
            NumberAnimation {
                properties: "rotation, position"
                duration: 1000
            }
        }
    ]
}

/*##^##
Designer {
    D{i:0;autoSize:true;formeditorZoom:1.75;height:480;width:640}
}
##^##*/

