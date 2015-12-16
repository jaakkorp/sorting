#ifndef SHELLSORT_H
#define SHELLSORT_H

#include "sortingalgorithm.h"

class ShellSort : public SortingAlgorithm
{
public:
    explicit ShellSort(SortEngineWorker *worker);

    virtual void sort();

private:
    void shellSort();
};

#endif // SHELLSORT_H
