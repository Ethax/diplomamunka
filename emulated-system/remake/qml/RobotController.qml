import QtQuick 2.14
import "qrc:/common"

Item {
    id: robotController

    property int robotNumber: 0
    property bool enabled: false

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
        if (enabled) {
            stopwatch.reset()
        } else if (stopwatch.hasExpired(50)) {
            getSelectedRobots().forEach(function (robot) {
                robot.accelerated = accelerated
                robot.suspended = suspended
                robot.position = position
                robot.toolActive = toolActive
            })
        }
    }

    Stopwatch {
        id: stopwatch
    }
}
