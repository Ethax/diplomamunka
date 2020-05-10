import QtQuick 2.14

State {
    property Item bridge
    property real position

    PropertyChanges {
        target: bridge
        anchors.topMargin: Math.round(position)
    }
}
