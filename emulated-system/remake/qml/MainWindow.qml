import QtQuick 2.14
import QtQuick.Window 2.14
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
                carBody.attachTo(master)
            } else {
                carBody.attachTo(mainWindow.contentItem)
            }
        }
    }

    Crane {
        id: crane
        x: 711
        y: 40
    }

    //    CarBody {
    //        id: carBody
    //        bodyType: CarBody.TypeOne
    //        x: 508
    //        y: 319

    //        Component.onCompleted: {
    //            attachTo(trolley)
    //            z = -2
    //        }
    //    }

    //    Trolley {
    //        x: 552
    //        y: 332
    //    }
    ToggleButton {
        id: toggleButton
        x: 517
        y: 433
        text: qsTr("Open/Close")

        onClicked: {
            if (checked) {
                crane.bridgePosition = crane.height
            } else {
                crane.bridgePosition = crane.height / 3.0
            }
        }
    }
}
