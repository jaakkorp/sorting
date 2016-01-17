#ifndef SELECTIONSORT_H
#define SELECTIONSORT_H

#include "sortingalgorithm.h"

class SelectionSort : public SortingAlgorithm
{
public:
    explicit SelectionSort(SortEngineWorker *worker);

    void sort(const QList<float> &list) override;
    Algorithm sortingAlgorithm() override;

private:
    void selectionSort();
};

#endif // SELECTIONSORT_H
