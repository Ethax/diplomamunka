import QtQuick 2.14

Item {
    id: element

    property int position: 0
    property bool open: false
    property alias attachPoint: hook

    implicitHeight: runwayBeam.height
    implicitWidth: bridge.width

    onPositionChanged: {
        switch (position >> 1) {
        case 0:
            bridge.y = runwayBeam.y + Math.round(2 * bridge.stepSize)
            break
        case 1:
            bridge.y = runwayBeam.y + Math.round(bridge.stepSize)
            break
        case 2:
            bridge.y = runwayBeam.y
            break
        case 3:
            bridge.y = runwayBeam.y + Math.round(3 * bridge.stepSize)
            break
        default:
            console.exception("Invalid position:", position)
            return
        }

        switch (position & 1) {
        case 0:
            trolley.anchors.leftMargin = 0
            break
        case 1:
            trolley.anchors.leftMargin = bridge.width / 4
            break
        }
    }

    onOpenChanged: trolley.clampOffset = open ? trolley.height / 2 : 0

    Image {
        id: runwayBeam

        source: "RunwayBeam.png"
        anchors.right: bridge.right
    }

    Image {
        id: rightFork

        source: "RightFork.png"
        anchors.horizontalCenter: trolley.horizontalCenter
        anchors.top: rightClamp.top
    }

    Image {
        id: leftFork

        source: "LeftFork.png"
        anchors.horizontalCenter: trolley.horizontalCenter
        anchors.bottom: leftClamp.bottom
    }

    Item {
        id: hook // attachPoint

        anchors.horizontalCenter: trolley.horizontalCenter
        anchors.verticalCenter: trolley.verticalCenter
    }

    Image {
        id: rightClamp

        source: "RightClamp.png"
        anchors.horizontalCenter: trolley.horizontalCenter
        anchors.verticalCenter: trolley.top
        anchors.verticalCenterOffset: -trolley.clampOffset

        Behavior on anchors.verticalCenterOffset {
            NumberAnimation {
                duration: 2000
            }
        }
    }

    Image {
        id: leftClamp

        source: "LeftClamp.png"
        anchors.horizontalCenter: trolley.horizontalCenter
        anchors.verticalCenter: trolley.bottom
        anchors.verticalCenterOffset: trolley.clampOffset

        Behavior on anchors.verticalCenterOffset {
            NumberAnimation {
                duration: 2000
            }
        }
    }

    Image {
        id: bridge

        property real stepSize: (runwayBeam.height - height) / 3.0

        source: "Bridge.png"
        anchors.right: parent.right
        y: Math.round(2 * stepSize)

        Behavior on y {
            id: bridgeMotion

            NumberAnimation {
                easing.type: Easing.InOutCubic
                duration: {
                    var distance = Math.abs(bridge.y - bridgeMotion.targetValue)
                    var numberOfSteps = Math.round(distance / bridge.stepSize)

                    return 6000 * numberOfSteps
                }
            }
        }
        visible: true
    }

    Image {
        id: trolley

        property int clampOffset: 0

        source: "Trolley.png"
        anchors.verticalCenter: bridge.verticalCenter
        anchors.left: bridge.left

        Behavior on anchors.leftMargin {
            NumberAnimation {
                duration: 5000
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}D{i:8;anchors_x:5}
}
##^##*/

