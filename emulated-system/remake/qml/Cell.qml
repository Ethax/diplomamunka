import QtQuick 2.14
import "qrc:/body"

Item {
    id: cell

    property Item nextCell: parent
    property bool active: false
    property var carBodies: []

    readonly property alias bodyEntered: entrySensor.active
    readonly property alias bodyArrived: arrivalSensor.active

    function onMoveFinished(body) {
        body.detectable = false
        body.attachTo(nextCell)
        body.detectable = true
    }

    onChildrenChanged: {
        carBodies.forEach(body => body.moveFinished.disconnect(onMoveFinished))

        carBodies = Array.from(children).filter(item => item instanceof CarBody)
        carBodies.forEach(body => body.moveFinished.connect(onMoveFinished))

        activeChanged()
    }

    onActiveChanged: {
        if (active) {
            carBodies.forEach(body => body.move(width - body.width / 2))
        } else {
            carBodies.forEach(body => body.stop())
        }
    }

    Sensor {
        id: entrySensor

        activeColor: "yellow"
        active: carBodies.some(detects)

        anchors {
            left: cell.left
            leftMargin: Math.round(cell.width / 5.0)
        }
    }

    Sensor {
        id: arrivalSensor

        activeColor: "green"
        active: carBodies.some(detects)

        anchors {
            right: cell.right
            rightMargin: Math.round(cell.width / 4.0)
        }
    }
}
