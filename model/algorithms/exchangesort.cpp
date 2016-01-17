#include "exchangesort.h"
#include "constants.h"

ExchangeSort::ExchangeSort(SortEngineWorker *worker)
    : SortingAlgorithm(worker)
{
}

void ExchangeSort::sort(const QList<float> &list)
{
    m_list = list;

    exchangeSort();
}

Algorithm ExchangeSort::sortingAlgorithm()
{
    return Algorithm::ExchangeSort;
}

void ExchangeSort::exchangeSort()
{
    for (auto i(0); i < m_list.count() - 1 ; ++i) {
        for (auto j(i + 1); j < m_list.count(); ++j) {
            if(m_list[i] > m_list[j]) {
                swap(i, j);
            }
        }
    }
}

