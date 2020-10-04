import QtQuick 2.14
import "qrc:/common"

Item {
    id: conveyorBelt

    property Item scene: parent
    property int activeBelts: 0

    function tryTakeOver(animatedItem) {}

    function tryHandOver(animatedItem) {}

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
            color: "#868686"
            border.color: "black"
        }
    }

    HorizontalRepeater {
        id: cells

        Item {
            property Item nextCell: scene
            property bool active: (activeBelts >> index) & 1

            height: displayedImages.itemAt(index).height
            width: displayedImages.itemAt(index).width

            function convey(animatedItem) {
                var destination = width - (animatedItem.width / 2)

                animatedItem.move(destination)
            }

            function stop(animatedItem) {
                animatedItem.stop()
            }
        }
    }
}
