#ifndef INSERTIONSORT_H
#define INSERTIONSORT_H

#include "sortingalgorithm.h"

class InsertionSort : public SortingAlgorithm
{
public:
    explicit InsertionSort(SortEngineWorker *worker);

    void sort(const QList<float> &list) override;
    Algorithm sortingAlgorithm() override;

private:
    void insertionSort();
};

#endif // INSERTIONSORT_H
