import QtQuick 2.5
import Qt.labs.sortboxmodel 1.0
import QtQuick.Controls 1.4
import QtQuick.Window 2.2

ApplicationWindow {
    id: root

    Component.onCompleted: visibility = Window.Maximized

    Rectangle {
        id: container

        height: root.height
        width: root.width

        Column {
            id: column

            anchors.centerIn: container
            spacing: 30

            Grid {
                id: grid
                columns: Math.ceil(Math.sqrt(sorterModel.count))
                rows: Math.ceil(Math.sqrt(sorterModel.count))
                spacing: 30
                property int itemHeight: 324
                property int itemWidth: 576

                add: Transition {
                    NumberAnimation { property: "opacity"; from: 0; to: 1.0; duration: 500 }
                    NumberAnimation { property: "scale"; from: 0; to: 1.0; easing.type: Easing.OutCirc; duration: 500 }
                }
                move: Transition {
                    NumberAnimation { property: "x"; easing.type: Easing.OutCirc; duration: 500 }
                    NumberAnimation { property: "y"; easing.type: Easing.OutCirc; duration: 500 }
                }

                Repeater {
                    id: sorters
                    model: sorterModel
                    Sorter {
                        id: sorter
                        height: grid.itemHeight
                        width: grid.itemWidth
                        barCount: count
                        sortingAlgorithm: algorithm
                        onSortedChanged: if (sorted && needResult) {
                                             sorter.result = results.getResult()
                                             internal.sorted(sorter.sortingTime)
                                         }
                        onClosed: internal.deleteSorter(index)
                    }
                }
            }

            Rectangle {
                width: grid.width

                Component.onCompleted: height = childrenRect.height

                Row {
                    anchors.centerIn: parent

                    spacing: 20

                    Button {
                        text: "Select all"
                        enabled: !internal.sorting
                        onClicked: internal.selectAll()
                    }

                    Button {
                        text: "Deselect all"
                        enabled: !internal.sorting
                        onClicked: internal.deselectAll()
                    }

                    Button {
                        text: "Sort"
                        enabled: !internal.sorting
                        onClicked: internal.sortSelected()
                    }

                    Button {
                        text: "Scramble"
                        enabled: !internal.sorting
                        onClicked: {
                            for (var i = 0; i < sorters.count; i++) {
                                if (sorters.itemAt(i).selected)
                                    sorters.itemAt(i).scramble()
                            }
                        }
                    }

                    Button {
                        text: "Set reverse order"
                        enabled: !internal.sorting
                        onClicked: internal.setReverseOrder()
                    }

                    Button {
                        text: "Set same order"
                        enabled: !internal.sorting
                        onClicked: internal.setRandomOrder()
                    }

                    Button {
                        text: "Set sorted unsorted"
                        enabled: !internal.sorting
                        onClicked: internal.setSortedFalse()
                    }

                    Button {
                        text: "Add sorter"
                        enabled: sorterModel.count < 6
                        onClicked: internal.addSorter()
                    }

                    ComboBox {
                        id: comboBox
                        width: grid.itemWidth / 4
                        onCurrentIndexChanged: {
                            for (var i = 0; i < sorters.count; i++)
                                if (sorters.itemAt(i).selected)
                                    sorters.itemAt(i).sortingAlgorithm = currentIndex
                        }
                        model: ListModel {
                            ListElement { text : "Bubble sort"; }
                            ListElement { text : "Exchange sort"; }
                            ListElement { text : "Selection sort"; }
                            ListElement { text : "Insertion sort"; }
                            ListElement { text : "Shell sort"; }
                            ListElement { text : "Merge sort"; }
                            ListElement { text : "Quick sort"; }
                        }
                    }
                }
            }
        }
    }

    ListModel {
        id: sorterModel

        ListElement {
            count: 100
            algorithm: SortBoxModel.QuickSort
        }

        ListElement {
            count: 100
            algorithm: SortBoxModel.QuickSort
        }

        ListElement {
            count: 100
            algorithm: SortBoxModel.QuickSort
        }

        ListElement {
            count: 100
            algorithm: SortBoxModel.QuickSort
        }

        ListElement {
            count: 100
            algorithm: SortBoxModel.QuickSort
        }

        ListElement {
            count: 100
            algorithm: SortBoxModel.QuickSort
        }
    }

    SortBoxModel {
        id: sortBoxModel
    }

    RaceResults {
        id: results
    }

    ReadySteadyGo {
        id: readySteadyGo
    }

    QtObject {
        id: internal
        property bool componentReady: false
        property bool sorting
        property int sortingItemsCount
        property int sortedItemsCount

        Component.onCompleted: componentReady = true

        function sortSelected() {
            reset()
            var initTime = readySteadyGo.initTime()
            for (var i = 0; i < sorters.count; i++) {
                if (sorters.itemAt(i).selected && !sorters.itemAt(i).sorting && !sorters.itemAt(i).sorted) {
                    sortingItemsCount++
                    sorters.itemAt(i).sort(initTime)
                    sorting = true
                }
            }
        }

        function selectAll() {
            for (var i = 0; i < sorters.count; i++)
                sorters.itemAt(i).selected = true
        }

        function deselectAll() {
            for (var i = 0; i < sorters.count; i++)
                sorters.itemAt(i).selected = false
        }

        function sorted(sortingTime) {
            sortedItemsCount++
            results.addRaceTime(sortingTime)
            if (sortedItemsCount === sortingItemsCount) {
                for (var j = 0; j < sorters.count; j++) {
                    if (sorters.itemAt(j).selected && !sorters.itemAt(j).sorting) {
                        sorters.itemAt(j).result = results.getResult(sorters.itemAt(j).sortingTime)
                    }
                }
            }
            sorting = false
        }

        function setReverseOrder() {
            var array = sortBoxModel.reverseOrder(100)
            for (var i = 0; i < sorters.count; i++)
                if (sorters.itemAt(i).selected)
                    sorters.itemAt(i).setOrder(array)
        }

        function setRandomOrder() {
            var array = sortBoxModel.randomOrder(100)
            for (var i = 0; i < sorters.count; i++)
                if (sorters.itemAt(i).selected)
                    sorters.itemAt(i).setOrder(array)
        }

        function setSortedFalse() {
            for (var i = 0; i < sorters.count; i++)
                if (sorters.itemAt(i).selected)
                    sorters.itemAt(i).setSortedFalse()
        }

        function addSorter() {
            if (sorterModel.count < 6)
                sorterModel.insert(sorterModel.count, {"count": 100, "algorithm": SortBoxModel.QuickSort});
        }

        function deleteSorter(index) {
            if (sorterModel.count > 1) {
                if (sorting && (sorters.itemAt(index).aboutToSort || sorters.itemAt(index).sorting))
                    sortingItemsCount--
                sorterModel.remove(index, 1)
            }
        }

        function reset() {
            sortingItemsCount = sortedItemsCount = 0
            results.reset()
        }
    }
}
