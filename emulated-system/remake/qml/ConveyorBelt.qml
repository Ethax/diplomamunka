import QtQuick 2.14
import "qrc:/common"
import "qrc:/"

Item {
    id: conveyorBelt

    property Item scene: parent
    property int activeBelts: 0

    function tryConvey(animatedItem) {
        for (var i = 0; i < cells.itemCount; ++i) {
            if (animatedItem.overlaps(cells.itemAt(i))) {
                animatedItem.attachTo(cells.itemAt(i))
                break
            }
        }
    }

    function tryLeave(animatedItem) {
        for (var i = 0; i < cells.itemCount; ++i) {
            if (animatedItem.attachedTo(cells.itemAt(i))) {
                animatedItem.stop()
                animatedItem.attachTo(scene)
            }
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

        Item {
            property Item nextCell: scene
            property bool active: (activeBelts >> index) & 1
            property var conveyedItems: []

            height: displayedImages.itemAt(index).height
            width: displayedImages.itemAt(index).width

            function onDestinationReached(item) {
                item.attachTo(nextCell)
            }

            onChildrenChanged: {
                var arrayOfChildren = Array.from(children)

                var removedItems = conveyedItems.filter(function (item) {
                    return !arrayOfChildren.includes(item)
                })
                removedItems.forEach(function (item) {
                    console.log("Unregister")
                    item.destinationReached.disconnect(onDestinationReached)
                })

                var addedItems = arrayOfChildren.filter(function (item) {
                    return !conveyedItems.includes(item)
                })
                addedItems.forEach(function (item) {
                    console.log("Register")
                    item.destinationReached.connect(onDestinationReached)
                })

                conveyedItems = arrayOfChildren
                activeChanged()
            }

            onActiveChanged: {
                if (active) {
                    conveyedItems.forEach(function (item) {
                        console.log("Start!")
                        console.log("[ x:", item.x, "| y:", item.y, "]")
                        item.move(width - (item.width / 2))
                    })
                } else {
                    conveyedItems.forEach(function (item) {
                        console.log("Stop!")
                        console.log("[ x:", item.x, "| y:", item.y, "]")
                        item.stop()
                    })
                }
            }

            Component.onCompleted: {
                if (index > 0) {
                    cells.itemAt(index - 1).nextCell = this
                }
            }
        }
    }
}
