import QtQuick 2.14

Item {
    id: stopwatch
    
    property real startTime: 0
    
    function reset() {
        startTime = Date.now()
    }
    
    function hasExpired(timeout) {
        return Date.now() - startTime >= timeout
    }
}
