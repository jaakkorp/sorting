#ifndef SORTINGALGORITHM_H
#define SORTINGALGORITHM_H

#include <QList>

class SortEngineWorker;
enum class Algorithm;

class SortingAlgorithm
{
public:
    SortingAlgorithm(SortEngineWorker *worker);
    // SortingAlgorithm is not designed to be copied or moved in the context
    // of this application. Therefore skipping "rule of five" guidelines.
    virtual ~SortingAlgorithm() = default;

    virtual void sort(const QList<float> &list) = 0;
    virtual Algorithm sortingAlgorithm() = 0;

protected:
    void swap(int index1, int index2);
    void replace(int index, float value);

protected:
    SortEngineWorker *m_worker;
    QList<float> m_list;
    Algorithm m_sortingAlgorithm;
};

#endif // SORTINGALGORITHM_H
