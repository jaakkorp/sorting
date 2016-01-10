#include "quicksort.h"
#include "constants.h"

QuickSort::QuickSort(SortEngineWorker *worker)
    : SortingAlgorithm(worker)
{
}

void QuickSort::sort()
{
    quickSort(0, m_list.count() - 1);
}

int QuickSort::sortingAlgorithm()
{
    return KQuickSort;
}

void QuickSort::quickSort(int left, int right)
{
    if (left < right) {
        auto pivot = (left + right) / 2;
        auto pivotNew = partition(left, right, pivot);

        quickSort(left, pivotNew - 1);
        quickSort(pivotNew + 1, right);
    }
}

int QuickSort::partition(int left, int right, int pivotIndex)
{
    auto pivot = m_list[pivotIndex];

    do {
        while (m_list[left] < pivot)
            ++left;

        while (m_list[right] > pivot)
            --right;

        if (left < right && m_list[left] != m_list[right]) {
            swap(left, right);
        } else {
            return right;
        }
    } while (left < right);

    return right;
}
