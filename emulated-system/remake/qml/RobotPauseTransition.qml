import QtQuick 2.14

Transition {
    property var robotArm

    readonly property real distance: robotArm.paused ? distance : robotArm.distance
    readonly property real lowering: robotArm.paused ? lowering : robotArm.lowering
    readonly property real rotation: robotArm.paused ? rotation : robotArm.rotation

    to: "pause"

    PropertyAction {
        target: robotArm
        property: "distance"
        value: distance
    }

    PropertyAction {
        target: robotArm
        property: "lowering"
        value: lowering
    }

    PropertyAction {
        target: robotArm
        property: "rotation"
        value: rotation
    }
}
