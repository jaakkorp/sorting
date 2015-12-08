import QtQuick 2.5
import Qt.labs.sortboxmodel 1.0
import QtQuick.Controls 1.4
import QtQuick.Window 2.2
import QtQuick.Layouts 1.2

ApplicationWindow {
    id: root

    Component.onCompleted: visibility = Window.Maximized

    ColumnLayout {
        id: column

        anchors.centerIn: parent
        spacing: 30

        Grid {
            id: grid

            Layout.alignment: Qt.AlignHCenter

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
                    height: grid.itemHeight
                    width: grid.itemWidth
                    barCount: count
                    sortingAlgorithm: algorithm
                    onSortedChanged: if (sorted && needResult) {
                                         result = results.getResult()
                                         internal.sorted(sortingTime)
                                     }
                    onClosed: internal.deleteSorter(index)

                    Component.onCompleted: {
                        selectAll.clicked.connect(function() {
                            selected = true
                        })

                        deselectAll.clicked.connect(function() {
                            selected = false
                        })

                        scrambleOrder.clicked.connect(function() {
                            if (selected)
                                scramble()
                        })

                        setUnsorted.clicked.connect(function() {
                            if (selected)
                                setSortedFalse()
                        })

                        internal.race.connect(function() {
                            if (sort(internal.initTime)) {
                                internal.sortingItemsCount++
                                internal.racing = true
                            }
                        })
                    }
                }
            }
        }

        RowLayout {
            Layout.alignment: Qt.AlignHCenter
            spacing: 20

            Button {
                id: selectAll

                text: "Select all"
                enabled: !internal.racing
            }

            Button {
                id: deselectAll

                text: "Deselect all"
                enabled: !internal.racing
            }

            Button {
                text: "Sort"
                enabled: !internal.racing
                onClicked: internal.sortSelected()
            }

            Button {
                id: scrambleOrder

                text: "Scramble"
                enabled: !internal.racing
                onClicked: {
                    for (var i = 0; i < sorters.count; i++) {
                        if (sorters.itemAt(i).selected)
                            sorters.itemAt(i).scramble()
                    }
                }
            }

            Button {
                text: "Set reverse order"
                enabled: !internal.racing
                onClicked: internal.setReverseOrder()
            }

            Button {
                text: "Set same order"
                enabled: !internal.racing
                onClicked: internal.setRandomOrder()
            }

            Button {
                id: setUnsorted

                text: "Set sorted unsorted"
                enabled: !internal.racing
                onClicked: internal.setSortedFalse()
            }

            Button {
                text: "Add sorter"
                enabled: sorterModel.count < 6
                onClicked: internal.addSorter()
            }

            ComboBox {
                id: comboBox

                Layout.minimumWidth: 150
                enabled: !internal.racing

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

        property bool racing
        property int sortingItemsCount
        property int sortedItemsCount
        property var initTime

        signal race

        function sortSelected() {
            reset()
            initTime = readySteadyGo.initTime()
            race()
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

                racing = false
            }
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

        function addSorter() {
            if (sorterModel.count < 6)
                sorterModel.insert(sorterModel.count, {"count": 100, "algorithm": SortBoxModel.QuickSort});
        }

        function deleteSorter(index) {
            if (sorterModel.count > 1) {
                if (racing && (sorters.itemAt(index).aboutToSort || sorters.itemAt(index).sorting))
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
