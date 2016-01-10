#ifndef MERGESORT_H
#define MERGESORT_H


#include "sortingalgorithm.h"

class MergeSort : public SortingAlgorithm
{
public:
    explicit MergeSort(SortEngineWorker *worker);

    void sort() override;
    int sortingAlgorithm() override;

private:
    void mergeSort(int p, int r);
    void merge(int p, int r);
};

#endif // MERGESORT_H
