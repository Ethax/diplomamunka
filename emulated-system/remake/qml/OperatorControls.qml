import QtQuick 2.14
import QtQuick.Controls.Styles 1.4
import QtQuick.Extras 1.4

Row {
    id: userControls

    readonly property alias factoryResetInitiated: factoryReset.checked
    readonly property alias emergencyStopActive: emergencyStop.checked
    readonly property alias acknowledged: acknowledge.checked
    readonly property alias selectedOperation: operation.selection

    spacing: 10

    OperatorButton {
        id: factoryReset

        text: qsTr("Reset")
        activeColor: "#0040ff"
        activeShadowColor: "#668cff"

        anchors.verticalCenter: userControls.verticalCenter
    }

    OperatorButton {
        id: emergencyStop

        text: qsTr("Stop")
        checkable: true

        anchors.verticalCenter: userControls.verticalCenter
    }

    OperatorButton {
        id: acknowledge

        text: qsTr("Nyugta")
        activeColor: "#00ff00"
        activeShadowColor: "#66ff66"

        anchors.verticalCenter: userControls.verticalCenter
    }

    OperationSelector {
        id: operation

        anchors.verticalCenter: userControls.verticalCenter
    }
}
