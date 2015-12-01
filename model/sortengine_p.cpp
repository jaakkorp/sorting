#include "sortengine_p.h"
#include "sortengine.h"
#include "constants.h"

SortEnginePrivate::SortEnginePrivate(SortEngine *q)
    : q_ptr(q)
{
}

void SortEnginePrivate::sort()
{
        switch (mSortingAlgorithm) {
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

void SortEnginePrivate::bubbleSort()
{
    for (int i(mList.count()-1); i > 0; i--) {
        for (int j(mList.count()-1); j > 0; j--) {
            if(mList[j] < mList[j-1]) {
                swap(j, j-1);
            }
        }
    }
}

void SortEnginePrivate::exchangeSort()
{
    for (int i(0); i < mList.count() -1 ; i++) {
        for (int j(i+1); j < mList.count(); j++) {
            if(mList[i] > mList[j]) {
                swap(i, j);
            }
        }
    }
}

void SortEnginePrivate::selectionSort()
{
    for (int i(0); i < mList.count(); i++) {
        int last = mList.count() - 1;
        for (int j(last); j >= i; j--) {
            if (mList[j] < mList[last])
                last = j;
        }
        if (mList[last] < mList[i])
            swap(last, i);
    }
}

void SortEnginePrivate::insertionSort()
{
    for (int i(1); i < mList.count(); i++) {
        int j = i;
        while (j > 0 && mList[j-1] > mList[j]) {
            swap(j, j-1);
            j--;
        }
    }
}

void SortEnginePrivate::shellSort()
{
    bool flag(true);
    int d(mList.count());
    while (flag || d > 1) {
        flag = false;
        d = (d+1) / 2;
        for (int i(0); i < (mList.count() - d); i++) {
            if (mList[i+d] < mList[i]) {
                flag = true;
                swap(i+d, i);
            }
        }
    }
}

void SortEnginePrivate::mergeSort()
{
    mergeSort(0, mList.count() -1);
}

void SortEnginePrivate::mergeSort(int p, int r)
{
    if (p < r) {
        int mid = (p + r) / 2;
        mergeSort(p, mid);
        mergeSort(mid + 1, r);
        merge(p, r);
    }
}

void SortEnginePrivate::merge(int p, int r)
{
    int mid = (p + r) / 2;
    int i1 = 0;
    int i2 = p;
    int i3 = mid + 1;

    QList<float> temp;
    for (int i(0); i < r-p+1; i++)
        temp.append(0.0);

    while (i2 <= mid && i3 <= r)
        if (mList[i2] < mList[i3])
            temp[i1++] = mList[i2++];
        else
            temp[i1++] = mList[i3++];

    while (i2 <= mid)
        temp[i1++] = mList[i2++];

    while ( i3 <= r )
        temp[i1++] = mList[i3++];

    for (int i = p; i <= r; i++)
        replace(i, temp[i-p]);
}

void SortEnginePrivate::quickSort()
{
    quickSort(0, mList.count() - 1);
}

void SortEnginePrivate::quickSort(int left, int right)
{
    if (left < right) {
        int pivot = (left + right) / 2;
        int pivotNew = partition(left, right, pivot);
        quickSort(left, pivotNew - 1);
        quickSort(pivotNew + 1, right);
    }
}

int SortEnginePrivate::partition(int left, int right, int pivotIndex)
{
    float pivot = mList[pivotIndex];
    do {
        while (mList[left] < pivot) left++;
        while (mList[right] > pivot) right--;
        if (left < right && mList[left] != mList[right]) {
            swap(left, right);
        }
        else {
            return right;
        }
    }
    while (left < right);

    return right;
}

void SortEnginePrivate::swap(int index1, int index2)
{
    Q_Q(SortEngine);

    mList.swap(index1, index2);
    q->doSwap(index1, index2);

}

void SortEnginePrivate::replace(int index, float value)
{
    Q_Q(SortEngine);

    mList.replace(index, value);
    q->doReplace(index, value);
}
