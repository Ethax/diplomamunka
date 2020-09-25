import QtQuick 2.14

State {
    property Item bridge
    property real distance

    PropertyChanges {
        target: bridge
        anchors.topMargin: Math.round(distance)
    }
}
