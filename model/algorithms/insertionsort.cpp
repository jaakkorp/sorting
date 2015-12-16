#include "insertionsort.h"

InsertionSort::InsertionSort(SortEngineWorker *worker)
    : SortingAlgorithm(worker)
{
}

void InsertionSort::sort()
{
    insertionSort();
}

void InsertionSort::insertionSort()
{
    for (auto i(m_list.count() - 1); i > 0; --i) {
        for (auto j(m_list.count() - 1); j > 0; --j) {
            if(m_list[j] < m_list[j - 1]) {
                swap(j, j - 1);
            }
        }
    }
}

