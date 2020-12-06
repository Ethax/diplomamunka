import QtQuick 2.14
import "qrc:/common"

Item {
    id: conveyorBelt

    property Item scene: parent
    property int activeBelts: 0
    property alias beltCount: belts.itemCount

    readonly property alias lastBodyType: cells.lastBodyType

    function tryConvey(animatedItem) {
        var cell = cells.getItem(animatedItem.overlaps)

        if (cell !== undefined) {
            animatedItem.attachTo(cell)
            cells.lastBodyType = animatedItem.bodyType
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

        property int lastBodyType: BodyType.None
        property int arrivalSensors: 0 // arrivals in cells vagy valami ilyen
        property int destinationSensors: 0 // entrance and destination sensors

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

            Binding {
                target: cells
                property: "arrivalSensors"
                value: {
                    var bitMask = 1 << index

                    if (arriving) {
                        return cells.arrivalSensors | bitMask
                    } else {
                        return cells.arrivalSensors & ~bitMask
                    }
                }
            }
        }
    }
}
