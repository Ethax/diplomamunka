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
        selectedRobots.every(robot => robot.completed)
    }

    readonly property var selectedRobots: {
        Array.from(children).filter(robot => robot.number === robotNumber)
    }

    function operate(robot) {
        robot.accelerated = accelerated
        robot.suspended = suspended
        robot.position = position
        robot.toolActive = toolActive
    }

    onEnabledChanged: {
        if (enabled) {
            elapsedTimer.reset()
        } else if (elapsedTimer.hasExpired(50)) {
            selectedRobots.forEach(operate)
        }
    }

    ElapsedTimer {
        id: elapsedTimer
    }
}
