import QtQuick 2.14
import "qrc:/body"

Item {
    id: cell

    property Item nextCell: parent
    property bool active: false
    property var conveyedItems: []

    property bool itemEntered: {
        conveyedItems.some(item => entrySensor.detects(item))
    }

    property bool itemArrived: {
        conveyedItems.some(item => arrivalSensor.detects(item))
    }

    function onMoveEnded(item) {
        item.attachTo(nextCell)
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

        active: itemEntered
        activeColor: "yellow"

        anchors {
            left: cell.left
            leftMargin: 10
        }
    }

    Sensor {
        id: arrivalSensor

        active: itemArrived
        activeColor: "green"

        anchors {
            horizontalCenter: cell.horizontalCenter
            horizontalCenterOffset: 10
        }
    }
}
