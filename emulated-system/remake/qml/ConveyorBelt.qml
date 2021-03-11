import QtQuick 2.14
import "qrc:/common"
import "qrc:/body"

Item {
    id: conveyorBelt

    property Item scene: parent
    property int activeBelts: 0
    property alias beltCount: belts.itemCount

    readonly property alias lastBodyType: cells.lastBodyType

    function tryConvey(animatedItem) {
        var cell = cells.findItem(animatedItem.overlaps)

        if (cell !== undefined) {
            animatedItem.attachTo(cell)
            cells.lastBodyType = animatedItem.bodyType
        }
    }

    function tryLeave(animatedItem) {
        var cell = cells.findItem(animatedItem.attachedTo)

        if (cell !== undefined) {
            animatedItem.stop()
            animatedItem.attachTo(scene)
        }
    }

    implicitHeight: belts.height
    implicitWidth: belts.width

    HorizontalRepeater {
        id: belts

        Component.onCompleted: {
            cells.spacing = spacing
            cells.itemCount = itemCount
        }

        Belt {
            active: (activeBelts >> index) & 1
        }
    }

    HorizontalRepeater {
        id: cells

        property int lastBodyType: BodyType.None
        property int detectedEntries: 0
        property int detectedArrivals: 0

        Cell {
            nextCell: scene
            active: (activeBelts >> index) & 1

            height: belts.itemAt(index).height
            width: belts.itemAt(index).width

            Component.onCompleted: {
                if (index > 0) {
                    cells.itemAt(index - 1).nextCell = this
                }
            }

            onBodyEnteredChanged: {
                var bitMask = 1 << index

                if (bodyEntered) {
                    cells.detectedEntries |= bitMask
                } else {
                    cells.detectedEntries &= ~bitMask
                }

                console.log("Detected Entries:", cells.detectedEntries)
            }

            onBodyArrivedChanged: {
                var bitMask = 1 << index

                if (bodyArrived) {
                    cells.detectedArrivals |= bitMask
                } else {
                    cells.detectedArrivals &= ~bitMask
                }

                //console.log("Detected Arrivals:", cells.detectedArrivals)
            }
        }
    }
}
