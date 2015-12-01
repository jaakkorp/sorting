import QtQuick 2.0
import Qt.labs.sortboxmodel 1.0

Rectangle {
    id: root

    property int sortingAlgorithm
    property int barCount
    property alias animationDuration: sortBoxModel.operationInterval
    property alias sorting: sortBoxModel.sorting
    property alias sorted: sortBoxModel.sorted
    property alias operationCount: sortBoxModel.operationCount

    gradient: Gradient {
        GradientStop { id: gradientBegin; position: 0.0; color: "#FFFFE0" }
        GradientStop { id: gradientEnd; position: 1.0; color: "#FFFFF0" }
    }
    border.color: "midnightblue"
    border.width: 1

    onSortedChanged: if (sorted) sortedAnimation.start()

    Row {
        id: barRow
        objectName: "barRow"
        anchors.fill: parent
        spacing: 2

        Repeater {
            id: bars
            objectName: "bars"
            model: sortBoxModel
            delegate: Bar {
                height: barHeightRatio * root.height;
                width: (root.width - (root.barCount - 1) * barRow.spacing) / root.barCount
                y: root.height - height
                animationDuration: root.animationDuration ? root.animationDuration : 200
                onMovingChanged: if (moving)
                                     internal.barMoveInitiated()
                                 else
                                     internal.barMoveFinished()
            }
        }
    }

    SortBoxModel {
        id: sortBoxModel
        sortingAlgorithm: root.sortingAlgorithm
        size: root.barCount
        operationInterval: 0
    }

    SequentialAnimation {
        id: sortedAnimation
        ParallelAnimation {
            ColorAnimation { target: root; properties: "border.color"; to: "white"; easing.type: Easing.OutCubic; duration: 500 }
            ColorAnimation { target: gradientBegin; properties: "color"; to: "white"; easing.type: Easing.OutCubic; duration: 500 }
            ColorAnimation { target: gradientEnd; properties: "color"; to: "white"; easing.type: Easing.OutCubic; duration: 500 }
        }
        ParallelAnimation {
            ColorAnimation { target: root; properties: "border.color"; to: "midnightblue"; easing.type: Easing.InCubic; duration: 500 }
            ColorAnimation { target: gradientBegin; properties: "color"; to: "#FFFFE0"; easing.type: Easing.OutCubic; duration: 500 }
            ColorAnimation { target: gradientEnd; properties: "color"; to: "#FFFFF0"; easing.type: Easing.OutCubic; duration: 500 }
        }
    }

    function sort() {
        if (!sortBoxModel.sorted && !sortBoxModel.sorting)
            sortBoxModel.sort()
    }

    function scramble() {
        if (!sortBoxModel.sorting)
            bars.model.scramble()
    }

    function setOrder(array) {
        sortBoxModel.setOrder(array)
    }

    function setSortedFalse() {
        sortBox.sorted = false
    }

    QtObject {
        id: internal

        property int movingBarCount: 0

        function barMoveInitiated() {
            movingBarCount++
        }

        function barMoveFinished() {
            movingBarCount--
            if (movingBarCount === 0) {
                sortBoxModel.proceed()
            }
        }
    }
}
