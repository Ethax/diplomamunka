import QtQuick 2.14
import "qrc:/common"

Item {
    id: conveyorBelt

    property Item scene: parent
    property int activeBelts: 0
    property alias beltCount: belts.itemCount

    function tryConvey(animatedItem) {
        var cell = cells.getItem(animatedItem.overlaps)

        if (cell !== undefined) {
            animatedItem.attachTo(cell)
        }
    }

    function tryLeave(animatedItem) {
        var cell = cells.getItem(animatedItem.attachedTo)

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
        }
    }
}
