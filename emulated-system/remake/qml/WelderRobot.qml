import QtQuick 2.14

Item {

    id: robot

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

