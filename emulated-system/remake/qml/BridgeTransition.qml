import QtQuick 2.14

Transition {
    property alias duration: animation.duration

    reversible: true

    NumberAnimation {
        id: animation

        property: "anchors.topMargin"
        easing.type: Easing.InOutCubic
    }
}
