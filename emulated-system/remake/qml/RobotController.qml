import QtQuick 2.14

Item {
    property int robotNumber: 0
    property bool enabled: false
    property real enableTime: 0

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
            enableTime = Date.now()
        } else if (Date.now() - enableTime > 50) {
            getSelectedRobots().forEach(function (robot) {
                robot.accelerated = accelerated
                robot.suspended = suspended
                robot.position = position
                robot.toolActive = toolActive
            })
        }
    }
}
