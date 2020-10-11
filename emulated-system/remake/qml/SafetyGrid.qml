import QtQuick 2.14

Item {
    id: safetyGrid

    property Item base: parent

    implicitHeight: displayedImage.height
    implicitWidth: displayedImage.width

    anchors {
        left: base.left
        verticalCenter: base.verticalCenter
    }

    Image {
        id: displayedImage

        source: "qrc:/conveyor/SafetyGrid.png"
    }
}
