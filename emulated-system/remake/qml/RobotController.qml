import QtQuick 2.14

Item {
    property var robots: []
    property int robotNumber: 0
    property bool enabled: false
    property real risingTime: 0

    property bool accelerated: false
    property bool suspended: false
    property int position: 0
    property bool toolActive: false

    readonly property bool completed: {
        return getSelectedRobots().every(function (robot) {
            return robot.completed
        })
    }

    function getSelectedRobots() {
        return Array.from(children).filter(function (robot) {
            return robot.number === robotNumber
        })
    }

    onEnabledChanged: {
        if (typeof robots[robotNumber] === undefined) {
            console.exception("Invalid robot number:", robotNumber)
            return
        }

        if (enabled) {
            risingTime = Date.now()
        } else if (Date.now() - risingTime > 50) {
            robots[robotNumber].accelerated = accelerated
            robots[robotNumber].suspended = suspended
            robots[robotNumber].position = position
            robots[robotNumber].toolActive = toolActive
        }
    }
}
