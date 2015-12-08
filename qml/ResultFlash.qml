import QtQuick 2.5

Item {
    id: root
    anchors.fill: parent

    function showResult(result) {
        internal.result = result
        resultAnimation.start()
    }

    function clear() {
        result.text = ""
    }

    Text {
        id: flash
        anchors.centerIn: parent

        color: "midnightblue"
        font.bold: true
    }

    Text {
        id: result
        anchors.rightMargin: 10
        anchors.right: root.right
        anchors.bottomMargin: 5
        anchors.bottom: root.bottom

        color: "midnightblue"
        font.pointSize: root.height >= 10 ? root.height * 0.1 : 1
        font.bold: true
    }

    SequentialAnimation {
        id: resultAnimation
        PropertyAction { target: flash; property: "text"; value: internal.result }
        ParallelAnimation {
            NumberAnimation { target: flash; properties: "opacity"; from: 0.0; to: 1.0; duration: 200 }
            NumberAnimation { target: flash; properties: "font.pointSize"; easing.type: Easing.OutBack; from: root.height * 0.2; to: root.height * 0.7; duration: 600 }
        }
        PropertyAction { target: result; property: "text"; value: internal.result }
        ParallelAnimation {
            NumberAnimation { target: flash; properties: "opacity"; from: 1.0; to: 0.0; duration: 600 }
            NumberAnimation { target: result; properties: "opacity"; from: 0.0; to: 1.0; duration: 600 }
        }
        PropertyAction { target: flash; property: "text"; value: "" }
    }

    QtObject {
        id: internal
        property int result
    }
}
