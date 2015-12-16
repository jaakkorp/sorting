#ifndef SELECTIONSORT_H
#define SELECTIONSORT_H

#include "sortingalgorithm.h"

class SelectionSort : public SortingAlgorithm
{
public:
    explicit SelectionSort(SortEngineWorker *worker);

    virtual void sort();

private:
    void selectionSort();
};

#endif // SELECTIONSORT_H
