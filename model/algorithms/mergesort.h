#ifndef MERGESORT_H
#define MERGESORT_H

#include "sortingalgorithm.h"

class MergeSort : public SortingAlgorithm
{
public:
    explicit MergeSort(SortEngineWorker *worker);

    void sort(const QList<float> &list) override;
    Algorithm sortingAlgorithm() override;

private:
    void mergeSort(int p, int r);
    void merge(int p, int r);
    inline int middle(int p, int r) { return (p + r) / 2; }
};

#endif // MERGESORT_H
