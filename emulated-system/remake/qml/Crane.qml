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
        anchors.right: crane.right
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

        orientation: Clamp.Downward
        base: trolley
        position: crane.gripperOpen
    }

    Clamp {
        id: lowerClamp

        orientation: Clamp.Upward
        base: trolley
        position: crane.gripperOpen
    }

    Bridge {
        id: bridge

        base: runwayBeam
        position: crane.position >> 1
    }

    Trolley {
        id: trolley

        base: bridge
        position: crane.position & 1
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/

