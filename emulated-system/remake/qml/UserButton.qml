import QtQuick 2.14
import QtQuick.Controls.Styles 1.4
import QtQuick.Extras 1.4

Item {
    id: userButton

    property bool checkable: false
    property alias checked: displayedButton.checked

    property color activeColor: "#ff0000"
    property color activeShadowColor: "#ff6666"
    property alias text: displayedButton.text

    implicitHeight: displayedButton.height
    implicitWidth: displayedButton.width

    DelayButton {
        id: displayedButton

        height: width
        width: 75
        delay: 0

        onPressedChanged: {
            if (!userButton.checkable) {
                checked = pressed
            }
        }

        style: DelayButtonStyle {
            progressBarGradient: Gradient {
                GradientStop {
                    position: 0
                    color: activeShadowColor
                }

                GradientStop {
                    position: 1
                    color: activeColor
                }
            }
            progressBarDropShadowColor: activeShadowColor
        }
    }
}
