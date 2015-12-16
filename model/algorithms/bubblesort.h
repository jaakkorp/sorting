#ifndef BUBBLESORT_H
#define BUBBLESORT_H

#include "sortingalgorithm.h"

class BubbleSort : public SortingAlgorithm
{
public:
    explicit BubbleSort(SortEngineWorker *worker);

    virtual void sort();

private:
    void bubbleSort();
};

#endif // BUBBLESORT_H
