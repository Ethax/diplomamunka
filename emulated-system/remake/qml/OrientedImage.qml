import QtQuick 2.14

Image {
    id: displayedImage

    enum Orientation {
        Downward,
        Upward
    }

    property int orientation: OrientedImage.Upward

    Binding on rotation {
        when: orientation === OrientedImage.Downward
        value: 180
    }

    Binding on rotation {
        when: orientation === OrientedImage.Upward
        value: 0
    }
}
