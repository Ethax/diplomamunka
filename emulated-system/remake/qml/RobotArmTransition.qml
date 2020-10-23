import QtQuick 2.14

Transition {
    id: transition

    property bool useFastAnimation: false
    property alias properties: animation.properties

    signal started
    signal stopped

    SequentialAnimation {
        ScriptAction {
            script: transition.started()
        }
        SmoothedAnimation {
            id: animation

            velocity: transition.useFastAnimation ? 20 : 10
        }
        ScriptAction {
            script: transition.stopped()
        }
    }
}
