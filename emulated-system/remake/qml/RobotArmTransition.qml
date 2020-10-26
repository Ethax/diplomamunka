import QtQuick 2.14

Transition {
    property bool useFastAnimation: false
    property alias properties: animation.properties
    readonly property alias stopped: sequence.animationStopped

    SequentialAnimation {
        id: sequence

        property bool animationStopped: true

        ScriptAction {
            script: sequence.animationStopped = false
        }

        SmoothedAnimation {
            id: animation

            velocity: useFastAnimation ? 60 : 20
        }

        ScriptAction {
            script: sequence.animationStopped = true
        }
    }
}
