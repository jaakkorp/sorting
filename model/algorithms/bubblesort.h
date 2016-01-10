#ifndef BUBBLESORT_H
#define BUBBLESORT_H

#include "sortingalgorithm.h"

class BubbleSort : public SortingAlgorithm
{
public:
    explicit BubbleSort(SortEngineWorker *worker);

    void sort() override;
    Algorithm sortingAlgorithm() override;

private:
    void bubbleSort();
};

#endif // BUBBLESORT_H
