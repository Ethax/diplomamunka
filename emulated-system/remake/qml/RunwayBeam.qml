import QtQuick 2.14

Item {
    id: runwayBeam

    property Item base: parent

    implicitHeight: displayedImage.height
    implicitWidth: displayedImage.width

    anchors.right: base.right

    Image {
        id: displayedImage

        source: "qrc:/crane/RunwayBeam.png"
    }
}
