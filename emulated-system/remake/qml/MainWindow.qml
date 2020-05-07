import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Controls 2.14

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

    //    ToggleButton {
    //        id: move
    //        x: 100
    //        y: 300
    //        text: qsTr("Move")

    //        onClicked: {
    //            if (checked) {
    //                master.x = 700
    //            } else {
    //                master.x = 10
    //            }
    //        }
    //    }

    //    ToggleButton {
    //        id: attach
    //        x: 300
    //        y: 300
    //        text: qsTr("Attach")

    //        onClicked: {
    //            if (checked) {
    //                carBody.attachTo(master)
    //            } else {
    //                carBody.attachTo(mainWindow.contentItem)
    //            }
    //        }
    //    }
    Crane {
        id: crane
        x: 563
        y: 54
    }

    CarBody {
        id: carBody
        bodyType: CarBody.TypeOne
        x: 529
        y: 266

        Component.onCompleted: {
            attachTo(crane.attachPoint)
        }
    }

    Button {
        x: 190
        y: 440
        text: qsTr("Move crane")

        onClicked: {
            crane.position++
        }
    }

    Button {
        x: 050
        y: 440
        text: qsTr("Open/Close")

        onClicked: {
            crane.open ^= 1
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:3}
}
##^##*/

