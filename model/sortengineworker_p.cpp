#include "sortengineworker_p.h"
#include "sortengineworker.h"
#include "constants.h"

SortEngineWorkerPrivate::SortEngineWorkerPrivate(SortEngineWorker *q)
    : q_ptr(q)
    , m_operationInterval(0)
{
}

void SortEngineWorkerPrivate::sort()
{
        switch (m_sortingAlgorithm) {
        case KBubbleSort:
            bubbleSort();
            break;

        case KExchangeSort:
            exchangeSort();
            break;

        case KSelectionSort:
            selectionSort();
            break;

        case KInsertionSort:
            insertionSort();
            break;

        case KShellSort:
            shellSort();
            break;

        case KMergeSort:
            mergeSort();
            break;

        case KQuickSort:
            quickSort();
            break;

        default:
            return;
        }
}

void SortEngineWorkerPrivate::bubbleSort()
{
    for (auto i(m_list.count() - 1); i > 0; --i) {
        for (auto j(m_list.count() - 1); j > 0; --j) {
            if(m_list[j] < m_list[j - 1]) {
                swap(j, j - 1);
            }
        }
    }
}

void SortEngineWorkerPrivate::exchangeSort()
{
    for (auto i(0); i < m_list.count() - 1 ; ++i) {
        for (auto j(i + 1); j < m_list.count(); ++j) {
            if(m_list[i] > m_list[j]) {
                swap(i, j);
            }
        }
    }
}

void SortEngineWorkerPrivate::selectionSort()
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

void SortEngineWorkerPrivate::insertionSort()
{
    for (auto i(1); i < m_list.count(); ++i) {
        auto j = i;
        while (j > 0 && m_list[j - 1] > m_list[j]) {
            swap(j, j - 1);
            --j;
        }
    }
}

void SortEngineWorkerPrivate::shellSort()
{
    auto flag = true;
    auto d = m_list.count();

    while (flag || d > 1) {
        flag = false;
        d = (d + 1) / 2;

        for (auto i(0); i < (m_list.count() - d); ++i) {
            if (m_list[i + d] < m_list[i]) {
                flag = true;
                swap(i + d, i);
            }
        }
    }
}

void SortEngineWorkerPrivate::mergeSort()
{
    mergeSort(0, m_list.count() - 1);
}

void SortEngineWorkerPrivate::mergeSort(int p, int r)
{
    if (p < r) {
        auto mid = (p + r) / 2;
        mergeSort(p, mid);
        mergeSort(mid + 1, r);
        merge(p, r);
    }
}

void SortEngineWorkerPrivate::merge(int p, int r)
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

void SortEngineWorkerPrivate::quickSort()
{
    quickSort(0, m_list.count() - 1);
}

void SortEngineWorkerPrivate::quickSort(int left, int right)
{
    if (left < right) {
        auto pivot = (left + right) / 2;
        auto pivotNew = partition(left, right, pivot);

        quickSort(left, pivotNew - 1);
        quickSort(pivotNew + 1, right);
    }
}

int SortEngineWorkerPrivate::partition(int left, int right, int pivotIndex)
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

void SortEngineWorkerPrivate::swap(int index1, int index2)
{
    Q_Q(SortEngineWorker);

    m_list.swap(index1, index2);
    q->doSwap(index1, index2);

}

void SortEngineWorkerPrivate::replace(int index, float value)
{
    Q_Q(SortEngineWorker);

    m_list.replace(index, value);
    q->doReplace(index, value);
}
