import QtQuick 2.14

Item {
    id: bridge

    property int destination
    property int runwayLength
    property Item connection

    implicitHeight: displayedImage.height
    implicitWidth: displayedImage.width

    anchors.top: connection ? connection.top : undefined
    state: destination & 3

    states: [
        BridgeState {
            name: "0"
            bridge: bridge
            position: 2.0 * (runwayLength - height) / 3.0
        },
        BridgeState {
            name: "1"
            bridge: bridge
            position: (runwayLength - height) / 3.0
        },
        BridgeState {
            name: "2"
            bridge: bridge
            position: 0.0
        },
        BridgeState {
            name: "3"
            bridge: bridge
            position: runwayLength - height
        }
    ]

    transitions: [
        BridgeTransition {
            duration: 6000
        },
        BridgeTransition {
            from: "0"
            to: "2"
            duration: 12000
        },
        BridgeTransition {
            from: "1"
            to: "3"
            duration: 12000
        },
        BridgeTransition {
            from: "2"
            to: "3"
            duration: 18000
        }
    ]

    Image {
        id: displayedImage
        source: "Bridge.png"
    }
}
