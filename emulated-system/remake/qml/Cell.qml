import QtQuick 2.14
import "qrc:/body"

Item {
    id: cell

    property Item nextCell: parent
    property bool active: false
    property var conveyedItems: []
    readonly property alias itemEntered: entrySensor.active
    readonly property alias itemArrived: arrivalSensor.active

    function onMoveEnded(item) {
        item.detectable = false
        item.attachTo(nextCell)
        item.detectable = true
    }

    function registerAddedItems(items) {
        var addedItems = items.filter(item => !conveyedItems.includes(item))

        addedItems.forEach(item => item.moveEnded.connect(onMoveEnded))
    }

    function unregisterRemovedItems(items) {
        var removedItems = conveyedItems.filter(item => !items.includes(item))

        removedItems.forEach(item => item.moveEnded.disconnect(onMoveEnded))
    }

    onChildrenChanged: {
        var items = Array.from(children).filter(item => item instanceof CarBody)

        unregisterRemovedItems(items)
        registerAddedItems(items)

        conveyedItems = items
        activeChanged()
    }

    onActiveChanged: {
        if (active) {
            conveyedItems.forEach(item => item.move(width - item.width / 2))
        } else {
            conveyedItems.forEach(item => item.stop())
        }
    }

    Sensor {
        id: entrySensor

        activeColor: "yellow"
        active: conveyedItems.some(detects)

        anchors {
            left: cell.left
            leftMargin: Math.round(cell.width / 5.0)
        }
    }

    Sensor {
        id: arrivalSensor

        activeColor: "green"
        active: conveyedItems.some(detects)

        anchors {
            right: cell.right
            rightMargin: Math.round(cell.width / 4.0)
        }
    }
}
