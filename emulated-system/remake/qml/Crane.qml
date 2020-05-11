import QtQuick 2.14

Item {
    id: crane

    property int position: 0
    property bool gripperOpen: false
    property alias attachPoint: hook

    implicitHeight: runwayBeam.height
    implicitWidth: bridge.width

    onPositionChanged: {
        bridge.destination = position >> 1
        trolley.position = position & 1
    }

    onGripperOpenChanged: {

        //trolley.clampOffset = gripperOpen ? trolley.height / 2 : 0
    }

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
        anchors.verticalCenterOffset: 0

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
        anchors.verticalCenterOffset: 0

        Behavior on anchors.verticalCenterOffset {
            NumberAnimation {
                duration: 2000
            }
        }
    }

    Bridge {
        id: bridge

        connection: runwayBeam
        anchors.right: crane.right
        runwayLength: runwayBeam.height
    }

    Trolley {
        id: trolley

        connection: bridge
        runwayLength: bridge.width / 3
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/

