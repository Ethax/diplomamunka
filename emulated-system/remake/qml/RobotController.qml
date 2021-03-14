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

    readonly property var selectedRobots: {
        Array.from(children).filter(item => item.number === robotNumber)
    }

    readonly property int completions: {
        Array.from(children).reduce(groupByNumber, []).reduce(setCompletion, 0)
    }

    function groupByNumber(groups, item) {
        var number = item.number

        groups[number] = groups[number] || []
        groups[number].push(item)

        return groups
    }

    function setCompletion(accumulator, robots, index) {
        return accumulator | robots.every(robot => robot.completed) << index
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
