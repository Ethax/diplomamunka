import QtQuick 2.14

Item {
    property real startTime: 0

    function reset() {
        startTime = Date.now()
    }

    function elapsed() {
        return Date.now() - startTime
    }

    function hasExpired(timeout) {
        return elapsed() >= timeout
    }
}
