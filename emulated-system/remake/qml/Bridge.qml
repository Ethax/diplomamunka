import QtQuick 2.14

Item {
    id: bridge

    property Item base: parent
    property int position: 0

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
            distance: 2.0 * (base.height - height) / 3.0
        },
        BridgeState {
            name: "1"
            bridge: bridge
            distance: (base.height - height) / 3.0
        },
        BridgeState {
            name: "2"
            bridge: bridge
            distance: 0.0
        },
        BridgeState {
            name: "3"
            bridge: bridge
            distance: base.height - height
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
