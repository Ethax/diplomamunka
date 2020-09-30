import QtQuick 2.14
import "qrc:/common"

Item {
    id: crane

    property Item scene: parent
    property int position: 0
    property bool grappleOpen: false

    implicitHeight: runwayBeam.height
    implicitWidth: bridge.width

    function tryCatch(animatedItem) {
        if (animatedItem.overlaps(hook)) {
            animatedItem.attachTo(hook)
        }
    }

    function tryRelease(animatedItem) {
        if (animatedItem.attachedTo(hook)) {
            animatedItem.attachTo(scene)
        }
    }

    RunwayBeam {
        id: runwayBeam

        base: crane
    }

    Fork {
        id: leftFork

        base: leftGrapple
        orientation: Orientation.Downward
    }

    Fork {
        id: rightFork

        base: rightGrapple
        orientation: Orientation.Upward
    }

    Item {
        id: hook

        anchors.centerIn: trolley
    }

    Grapple {
        id: leftGrapple

        base: trolley
        orientation: Orientation.Downward
        open: crane.grappleOpen
    }

    Grapple {
        id: rightGrapple

        base: trolley
        orientation: Orientation.Upward
        open: crane.grappleOpen
    }

    Bridge {
        id: bridge

        base: runwayBeam
        position: crane.position >> 1
    }

    Trolley {
        id: trolley

        base: bridge
        raised: crane.position & 1
    }
}
