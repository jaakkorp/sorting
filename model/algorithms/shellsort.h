#ifndef SHELLSORT_H
#define SHELLSORT_H

#include "sortingalgorithm.h"

class ShellSort : public SortingAlgorithm
{
public:
    explicit ShellSort(SortEngineWorker *worker);

    void sort(const QList<float> &list) override;
    Algorithm sortingAlgorithm() override;

private:
    void shellSort();
};

#endif // SHELLSORT_H
