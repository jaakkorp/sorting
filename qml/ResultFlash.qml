import QtQuick 2.0

Text {
    id: root
    anchors.centerIn: parent
    color: "midnightblue"
    font.bold: true

    QtObject {
        id: internal
        property int result
    }

    SequentialAnimation {
        id: resultAnimation
        PropertyAction { target: root; property: "text"; value: internal.result }
        ParallelAnimation {
            NumberAnimation { target: root; properties: "opacity"; from: 0.0; to: 1.0; duration: 200 }
            NumberAnimation { target: root; properties: "font.pointSize"; easing.type: Easing.OutBack; from: root.parent.height * 0.2; to: root.parent.height * 0.7; duration: 600 }
        }
        NumberAnimation { target: root; properties: "opacity"; from: 1.0; to: 0.0; duration: 600 }
        PropertyAction { target: root; property: "text"; value: "" }
    }

    function showResult(result) {
        internal.result = result
        resultAnimation.start()
    }
}
