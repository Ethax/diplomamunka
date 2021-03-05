import QtQuick 2.14
import "qrc:/common"

Item {
    id: cell

    property Item nextCell: parent
    property bool active: false
    property bool itemEntered: false
    property bool itemArrived: false
    property var conveyedItems: []

    function onPositionChanged() {
        itemEntered = false
        itemArrived = false

        conveyedItems.forEach(function (item) {
            itemEntered |= item.overlaps(/* entrySensor */ )
            itemArrived |= item.overlaps(/* arrivalSensor */ )
        })
    }

    function onDestinationReached(item) {
        item.attachTo(nextCell)
    }

    function registerAddedItems(actualChildren) {
        var addedItems = actualChildren.filter(function (item) {
            return !conveyedItems.includes(item)
        })

        addedItems.forEach(function (item) {
            item.xChanged.connect(onPositionChanged)
            item.destinationReached.connect(onDestinationReached)
        })
    }

    function unregisterRemovedItems(actualChildren) {
        var removedItems = conveyedItems.filter(function (item) {
            return !actualChildren.includes(item)
        })

        removedItems.forEach(function (item) {
            item.xChanged.disconnect(onPositionChanged)
            item.destinationReached.disconnect(onDestinationReached)
        })
    }

    onChildrenChanged: {
        var actualChildren = Array.from(children)

        unregisterRemovedItems(actualChildren)
        registerAddedItems(actualChildren)

        conveyedItems = actualChildren
        activeChanged()
    }

    onActiveChanged: {
        if (active) {
            conveyedItems.forEach(function (item) {
                item.move(width - (item.width / 2))
            })
        } else {
            conveyedItems.forEach(function (item) {
                item.stop()
            })
        }
    }
}
