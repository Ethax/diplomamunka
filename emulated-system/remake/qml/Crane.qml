import QtQuick 2.14
import "qrc:/common"

Item {
    id: crane

    property int position: 0
    property bool grappleOpen: false

    implicitHeight: runwayBeam.height
    implicitWidth: bridge.width

    function tryRelease(attachableItem) {
        if (attachableItem.attachedTo(hook)) {
            attachableItem.release()
        }
    }

    function tryCatch(attachableItem) {
        if (attachableItem.overlaps(hook)) {
            attachableItem.attachTo(hook)
        }
    }

    RunwayBeam {
        id: runwayBeam

        base: crane
    }

    Fork {
        id: leftFork

        orientation: Orientation.Downward
        base: leftGrapple
    }

    Fork {
        id: rightFork

        orientation: Orientation.Upward
        base: rightGrapple
    }

    Item {
        id: hook

        anchors.centerIn: trolley
    }

    Grapple {
        id: leftGrapple

        orientation: Orientation.Downward
        base: trolley
        position: crane.grappleOpen
    }

    Grapple {
        id: rightGrapple

        orientation: Orientation.Upward
        base: trolley
        position: crane.grappleOpen
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
