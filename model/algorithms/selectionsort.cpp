#include "selectionsort.h"
#include "constants.h"

SelectionSort::SelectionSort(SortEngineWorker *worker)
    : SortingAlgorithm(worker)
{
}

void SelectionSort::sort()
{
    selectionSort();
}

int SelectionSort::sortingAlgorithm()
{
    return KSelectionSort;
}

void SelectionSort::selectionSort()
{
    for (auto i(0); i < m_list.count(); ++i) {
        auto last = m_list.count() - 1;

        for (auto j(last); j >= i; --j) {
            if (m_list[j] < m_list[last])
                last = j;
        }

        if (m_list[last] < m_list[i])
            swap(last, i);
    }
}
