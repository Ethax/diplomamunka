import QtQuick 2.14
import "qrc:/common"

Item {
    id: conveyorBelt

    property Item scene: parent
    property int activeBelts: 0

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

    implicitHeight: displayedImages.height
    implicitWidth: displayedImages.width

    HorizontalRepeater {
        id: displayedImages

        spacing: 5
        itemCount: 3

        Component.onCompleted: {
            cells.spacing = spacing
            cells.itemCount = itemCount
        }

        Rectangle {
            width: 250
            height: 75
            color: "gray"
            border.color: "black"
        }
    }

    HorizontalRepeater {
        id: cells

        Cell {
            nextCell: scene
            active: (activeBelts >> index) & 1

            height: displayedImages.itemAt(index).height
            width: displayedImages.itemAt(index).width

            Component.onCompleted: {
                if (index > 0) {
                    cells.itemAt(index - 1).nextCell = this
                }
            }
        }
    }
}
