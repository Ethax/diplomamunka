import QtQuick 2.14
import "qrc:/body"

Item {
    id: cell

    property Item nextCell: parent
    property bool active: false
    property var conveyedBodies: []

    readonly property alias bodyEntered: entrySensor.active
    readonly property alias bodyArrived: arrivalSensor.active

    function onMoveFinished(body) {
        body.detectable = false
        body.attachTo(nextCell)
        body.detectable = true
    }

    onChildrenChanged: {
        var currentBodies = Array.from(children).filter(
                    child => child instanceof CarBody)

        currentBodies.filter(body => !conveyedBodies.includes(body)).forEach(
                    body => body.moveFinished.connect(onMoveFinished))
        conveyedBodies.filter(body => !currentBodies.includes(body)).forEach(
                    body => body.moveFinished.disconnect(onMoveFinished))

        conveyedBodies = currentBodies
        activeChanged()
    }

    onActiveChanged: {
        if (active) {
            conveyedBodies.forEach(body => body.move(width - body.width / 2))
        } else {
            conveyedBodies.forEach(body => body.stop())
        }
    }

    Sensor {
        id: entrySensor

        activeColor: "yellow"
        active: conveyedBodies.some(detects)

        anchors {
            left: cell.left
            leftMargin: Math.round(cell.width / 5.0)
        }
    }

    Sensor {
        id: arrivalSensor

        activeColor: "green"
        active: conveyedBodies.some(detects)

        anchors {
            right: cell.right
            rightMargin: Math.round(cell.width / 4.0)
        }
    }
}
