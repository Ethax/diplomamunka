import QtQuick 2.14

Transition {
    property bool useFastAnimation: false
    property alias properties: animation.properties
    readonly property alias stopped: sequence.animationStopped

    property real startTime: 0

    SequentialAnimation {
        id: sequence

        property bool animationStopped: true

        ScriptAction {
            script: {
                console.log("Transition entered")

                startTime = Date.now()
                sequence.animationStopped = false
            }
        }

        NumberAnimation {
            id: animation

            duration: useFastAnimation ? 500 : 4000
        }

        ScriptAction {
            script: {
                console.log("Transition leaved")
                sequence.animationStopped = true
            }
        }
    }
}
