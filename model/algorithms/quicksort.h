#ifndef QUICKSORT_H
#define QUICKSORT_H

#include "sortingalgorithm.h"


class QuickSort : public SortingAlgorithm
{
public:
    explicit QuickSort(SortEngineWorker *worker);

    void sort(const QList<float> &list) override;
    Algorithm sortingAlgorithm() override;

private:
    void quickSort(int left, int right);
    int partition(int left, int right, int pivotIndex);

};

#endif // QUICKSORT_H
