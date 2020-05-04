import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Extras 1.4

Window {
    id: mainWindow
    visible: true
    width: 800
    height: 600

    Rectangle {
        id: master
        x: 10
        y: 10
        width: 50
        height: 50
        color: "#00ff00"

        Behavior on x {
            NumberAnimation {
                duration: 4000
                easing.type: Easing.InOutCubic

                onRunningChanged: {
                    if (!running) {
                        master.color = "#ff0000"
                    }
                }
            }
        }
    }

    Rectangle {
        property alias animationEnabled: behavior.enabled

        id: slave
        x: 100
        y: 100
        width: 50
        height: 50
        color: "#ff0000"

        Behavior on x {
            id: behavior

            NumberAnimation {
                duration: 1000
            }
        }

        function attachTo(item) {
            var newPoint = parent.mapToItem(item, x, y)

            parent = item
            x = newPoint.x
            y = newPoint.y
        }
    }

    ToggleButton {
        id: move
        x: 100
        y: 300
        text: qsTr("Move")

        onClicked: {
            if (checked) {
                master.x = 700
            } else {
                master.x = 10
            }
        }
    }

    ToggleButton {
        id: attach
        x: 300
        y: 300
        text: qsTr("Attach")

        onClicked: {
            if (checked) {
                slave.animationEnabled = false
                slave.attachTo(master)
            } else {
                slave.attachTo(mainWindow.contentItem)
                slave.animationEnabled = true
                slave.x = 200
            }
        }
    }
}
