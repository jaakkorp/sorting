#ifndef INSERTIONSORT_H
#define INSERTIONSORT_H

#include "sortingalgorithm.h"

class InsertionSort : public SortingAlgorithm
{
public:
    explicit InsertionSort(SortEngineWorker *worker);

    virtual void sort();

private:
    void insertionSort();
};

#endif // INSERTIONSORT_H
