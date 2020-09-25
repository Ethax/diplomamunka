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

    Fork {
        id: upperFork

        orientation: OrientedImage.Downward
        base: upperClamp
    }

    Fork {
        id: lowerFork

        orientation: OrientedImage.Upward
        base: lowerClamp
    }

    Item {
        id: attachPoint

        anchors.centerIn: trolley
    }

    Clamp {
        id: upperClamp

        orientation: OrientedImage.Downward
        base: trolley
        position: crane.gripperOpen
    }

    Clamp {
        id: lowerClamp

        orientation: OrientedImage.Upward
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

