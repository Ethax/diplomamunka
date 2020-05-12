import QtQuick 2.14

Item {
    id: crane

    property int position: 0
    property bool gripperOpen: false
    property alias attachPoint: attachPoint

    implicitHeight: runwayBeam.height
    implicitWidth: bridge.width

    Image {
        id: runwayBeam

        source: "RunwayBeam.png"
        anchors.right: bridge.right
    }

    Image {
        id: rightFork

        source: "RightFork.png"
        anchors.horizontalCenter: trolley.horizontalCenter
        anchors.top: upperClamp.top
    }

    Image {
        id: leftFork

        source: "LeftFork.png"
        anchors.horizontalCenter: trolley.horizontalCenter
        anchors.bottom: lowerClamp.bottom
    }

    Item {
        id: attachPoint

        anchors.centerIn: trolley
    }

    Clamp {
        id: upperClamp

        connection: trolley
        runwayLength: trolley.height / 2
        orientation: Clamp.Downward
        position: crane.gripperOpen
    }

    Clamp {
        id: lowerClamp

        connection: trolley
        runwayLength: trolley.height / 2
        orientation: Clamp.Upward
        position: crane.gripperOpen
    }

    Bridge {
        id: bridge

        connection: runwayBeam
        anchors.right: crane.right
        runwayLength: runwayBeam.height
        destination: crane.position >> 1
    }

    Trolley {
        id: trolley

        connection: bridge
        runwayLength: bridge.width / 3
        position: crane.position & 1
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/

