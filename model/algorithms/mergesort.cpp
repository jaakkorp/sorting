#include "mergesort.h"
#include "constants.h"

#include <QVector>

MergeSort::MergeSort(SortEngineWorker *worker)
    : SortingAlgorithm(worker)
{
}

void MergeSort::sort(const QList<float> &list)
{
    m_list = list;

    mergeSort(0, m_list.count() - 1);
}

Algorithm MergeSort::sortingAlgorithm()
{
    return Algorithm::MergeSort;
}

void MergeSort::mergeSort(int p, int r)
{
    if (p >= r)
        return;

    auto mid = middle(p, r);
    mergeSort(p, mid);
    mergeSort(mid + 1, r);
    merge(p, r);
}

void MergeSort::merge(int p, int r)
{
    auto mid = middle(p, r);
    auto i1 = 0;
    auto i2 = p;
    auto i3 = mid + 1;

    QVector<float> merged(r - p + 1);

    while (i2 <= mid && i3 <= r) {
        if (m_list[i2] < m_list[i3]) {
            merged[i1++] = m_list[i2++];
        }
        else {
            merged[i1++] = m_list[i3++];
        }
    }

    while (i2 <= mid)
        merged[i1++] = m_list[i2++];

    while (i3 <= r)
        merged[i1++] = m_list[i3++];

    for (auto i(p); i <= r; ++i) {
        if (m_list[i] != merged[i-p])
            replace(i, merged[i-p]);
    }
}

