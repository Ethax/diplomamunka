import QtQuick 2.14
import "qrc:/common"
import "qrc:/body"

Item {
    id: conveyorBelt

    property Item scene: parent
    property alias beltCount: belts.itemCount

    property int activeBelts: 0
    readonly property alias lastBodyType: cells.lastBodyType
    readonly property alias detectedEntries: cells.detectedEntries
    readonly property alias detectedArrivals: cells.detectedArrivals

    function tryConvey(carBody) {
        var cell = cells.findItem(carBody.overlaps)

        if (cell !== undefined) {
            carBody.attachTo(cell)
            cells.lastBodyType = carBody.bodyType
        }
    }

    function tryLeave(carBody) {
        var cell = cells.findItem(carBody.attachedTo)

        if (cell !== undefined) {
            carBody.stop()
            carBody.attachTo(scene)
        }
    }

    implicitHeight: belts.height
    implicitWidth: belts.width

    HorizontalRepeater {
        id: belts

        Component.onCompleted: cells.itemCount = itemCount

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
            }

            onBodyArrivedChanged: {
                var bitMask = 1 << index

                if (bodyArrived) {
                    cells.detectedArrivals |= bitMask
                } else {
                    cells.detectedArrivals &= ~bitMask
                }
            }
        }
    }
}
