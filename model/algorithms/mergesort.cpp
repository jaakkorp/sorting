#include "mergesort.h"
#include "constants.h"

MergeSort::MergeSort(SortEngineWorker *worker)
    : SortingAlgorithm(worker)
{
}

void MergeSort::sort()
{
    mergeSort(0, m_list.count() - 1);
}

Algorithm MergeSort::sortingAlgorithm()
{
    return Algorithm::MergeSort;
}

void MergeSort::mergeSort(int p, int r)
{
    if (p < r) {
        auto mid = (p + r) / 2;
        mergeSort(p, mid);
        mergeSort(mid + 1, r);
        merge(p, r);
    }
}

void MergeSort::merge(int p, int r)
{
    auto mid = (p + r) / 2;
    auto i1 = 0;
    auto i2 = p;
    auto i3 = mid + 1;

    QList<float> temp;
    for (auto i(0); i < r - p + 1; ++i)
        temp.append(0.0);

    while (i2 <= mid && i3 <= r)
        if (m_list[i2] < m_list[i3])
            temp[i1++] = m_list[i2++];
        else
            temp[i1++] = m_list[i3++];

    while (i2 <= mid)
        temp[i1++] = m_list[i2++];

    while (i3 <= r)
        temp[i1++] = m_list[i3++];

    for (auto i(p); i <= r; ++i)
        replace(i, temp[i-p]);
}

