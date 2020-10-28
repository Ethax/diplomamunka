import QtQuick 2.14

Transition {
    property var robotArm

    SequentialAnimation {
        PropertyAction {
            target: robotArm
            property: "completed"
            value: false
        }

        SmoothedAnimation {
            target: robotArm
            properties: "distance, lowering, rotation"
            velocity: robotArm.accelerated ? 60 : 20
        }

        PropertyAction {
            target: robotArm
            property: "completed"
            value: true
        }
    }
}
