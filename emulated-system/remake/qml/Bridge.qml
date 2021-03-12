import QtQuick 2.14

Item {
    id: bridge

    property Item base: parent
    property int position: 0

    readonly property real destinationHome: 2.0 * destinationThree / 3.0
    readonly property real destinationOne: 0.0
    readonly property real destinationTwo: destinationThree / 3.0
    readonly property real destinationThree: base.height - height

    implicitHeight: displayedImage.height
    implicitWidth: displayedImage.width

    anchors {
        top: base.top
        horizontalCenter: base.horizontalCenter
    }

    state: position & 3

    Image {
        id: displayedImage

        source: "qrc:/crane/Bridge.png"
    }

    states: [
        BridgeState {
            name: "0"
            bridge: bridge
            distance: destinationHome
        },
        BridgeState {
            name: "1"
            bridge: bridge
            distance: destinationTwo
        },
        BridgeState {
            name: "2"
            bridge: bridge
            distance: destinationOne
        },
        BridgeState {
            name: "3"
            bridge: bridge
            distance: destinationThree
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
}
