import QtQuick 2.14

Item {
    property alias interval: timer.interval
    property alias running: timer.running
    readonly property alias tick: timer.clockSignal

    Timer {
        id: timer

        property bool clockSignal: false

        repeat: true

        onTriggered: clockSignal = !clockSignal
        onRunningChanged: clockSignal = running ? clockSignal : false
    }
}
