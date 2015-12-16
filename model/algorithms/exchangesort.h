#ifndef EXCHANGESORT_H
#define EXCHANGESORT_H

#include "sortingalgorithm.h"

class ExchangeSort : public SortingAlgorithm
{
public:
    explicit ExchangeSort(SortEngineWorker *worker);

    virtual void sort();

private:
    void exchangeSort();
};

#endif // EXCHANGESORT_H
