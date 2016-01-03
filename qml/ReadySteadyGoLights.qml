import QtQuick 2.5

Item {
    id: root
    anchors.fill: parent

    function init() {
        initAnimation.start()
    }

    function ready() {
        readyAnimation.start()
    }

    function steady() {
        steadyAnimation.start()
    }

    function go() {
        goAnimation.start()
    }

    Rectangle {
        id: background
        anchors.fill: parent
        gradient: Gradient {
            GradientStop { position: 0.0; color: "gray" }
            GradientStop { position: 1.0; color: "lightgray" }
        }
        opacity: 0.0
    }

    Row {
        id: row
        anchors.centerIn: parent
        spacing: root.width / 10

        Rectangle {
            id: readyLights
            height: root.parent.height / 3
            width: height
            gradient: Gradient {
                GradientStop { position: 0.0; color: "red" }
                GradientStop { position: 1.0; color: "#B0171F" }
            }
            radius: width * 0.5
            opacity: 0.0
        }

        Rectangle {
            id: steadyLights
            height: root.parent.height / 3
            width: height
            gradient: Gradient {
                GradientStop { position: 0.0; color: "red" }
                GradientStop { position: 1.0; color: "#B0171F" }
            }

            radius: width * 0.5
            opacity: 0.0
        }

        Rectangle {
            id: goLights
            height: root.parent.height / 3
            width: height
            gradient: Gradient {
                GradientStop { position: 0.0; color: "#00FF00" }
                GradientStop { position: 1.0; color: "#006400" }
            }
            radius: width * 0.5
            opacity: 0.0
        }

        NumberAnimation {
            id: initAnimation
            target: background; properties: "opacity"; from: 0.0; to: 0.3; duration: 200
        }

        NumberAnimation {
            id: readyAnimation
            target: readyLights; properties: "opacity"; from: 0.0; to: 1.0; duration: 50
        }

        NumberAnimation {
            id: steadyAnimation
            target: steadyLights; properties: "opacity"; from: 0.0; to: 1.0; duration: 50
        }

        SequentialAnimation {
            id: goAnimation
            NumberAnimation { target: goLights; properties: "opacity"; from: 0.0; to: 1.0; duration: 50 }
            ParallelAnimation {
                NumberAnimation { target: readyLights; properties: "opacity"; from: 1.0; to: 0.0; duration: 1000 }
                NumberAnimation { target: steadyLights; properties: "opacity"; from: 1.0; to: 0.0; duration: 1000 }
                NumberAnimation { target: goLights; properties: "opacity"; from: 1.0; to: 0.0; duration: 1000 }
                NumberAnimation { target: background; properties: "opacity"; from: 0.3; to: 0.0; duration: 1000 }
            }
        }
    }
}
