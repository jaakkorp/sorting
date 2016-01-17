#include "shellsort.h"
#include "constants.h"

ShellSort::ShellSort(SortEngineWorker *worker)
    : SortingAlgorithm(worker)
{
}

void ShellSort::sort(const QList<float> &list)
{
    m_list = list;

    shellSort();
}

Algorithm ShellSort::sortingAlgorithm()
{
    return Algorithm::ShellSort;
}

void ShellSort::shellSort()
{
    auto flag = true;
    auto d = m_list.count();

    while (flag || d > 1) {
        flag = false;
        d = (d + 1) / 2;

        for (auto i(0); i < (m_list.count() - d); ++i) {
            if (m_list[i + d] < m_list[i]) {
                flag = true;
                swap(i + d, i);
            }
        }
    }
}

