import QtQuick 2.14
import "qrc:/common"

Item {
    id: operator

    readonly property alias operation: ticker.tick

    property real observationX: 0
    property real observationY: 0

    property real inspectionX: 0
    property real inspectionY: 0

    property real correctionX: 0
    property real correctionY: 0

    implicitHeight: displayedImage.height
    implicitWidth: displayedImage.width

    Image {
        id: displayedImage

        source: "qrc:/operator/Operator.png"
    }

    Ticker {
        id: ticker
    }

    state: Operation.Observation

    states: [
        State {
            name: Operation.Observation

            PropertyChanges {
                target: operator
                x: observationX
                y: observationY
            }

            PropertyChanges {
                target: ticker
                running: false
            }
        },
        State {
            name: Operation.Inspection

            PropertyChanges {
                target: operator
                x: inspectionX
                y: inspectionY
            }

            PropertyChanges {
                target: ticker
                running: true
                interval: 500
            }
        },
        State {
            name: Operation.Correction

            PropertyChanges {
                target: operator
                x: correctionX
                y: correctionY
            }

            PropertyChanges {
                target: ticker
                running: true
                interval: 250
            }
        }
    ]

    transitions: [
        Transition {
            NumberAnimation {
                target: operator
                properties: "x, y"
                easing.type: Easing.InOutCubic
                duration: 4000
            }
        }
    ]
}
