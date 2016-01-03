#ifndef SORTINGALGORITHM_H
#define SORTINGALGORITHM_H

#include <QList>

class SortEngineWorker;

class SortingAlgorithm
{
public:
    SortingAlgorithm(SortEngineWorker *worker);
    virtual ~SortingAlgorithm() {}

    virtual void sort() = 0;

    void swap(int index1, int index2);
    void replace(int index, float value);

    SortEngineWorker *m_worker;
    QList<float> m_list;

    int m_sortingAlgorithm;
};

#endif // SORTINGALGORITHM_H
