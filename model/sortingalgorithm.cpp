#include "sortingalgorithm.h"
#include "sortengineworker.h"
#include "constants.h"

SortingAlgorithm::SortingAlgorithm(SortEngineWorker *worker)
    : m_worker(worker)
    , m_sortingAlgorithm(Algorithm::QuickSort)
{
}

void SortingAlgorithm::swap(int index1, int index2)
{
    m_list.swap(index1, index2);
    m_worker->doSwap(index1, index2);

}

void SortingAlgorithm::replace(int index, float value)
{
    m_list.replace(index, value);
    m_worker->doReplace(index, value);
}
