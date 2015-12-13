#ifndef SORTENGINE_P_H
#define SORTENGINE_P_H

#include <QList>

class SortEngineWorker;

class SortEngineWorkerPrivate
{
    Q_DECLARE_PUBLIC(SortEngineWorker)

public:
    SortEngineWorkerPrivate(SortEngineWorker *q);

    void sort();

    // Sorting functions
    void bubbleSort();
    void exchangeSort();
    void selectionSort();
    void insertionSort();
    void shellSort();
    void mergeSort();
    void quickSort();

    // Utility functions
    void quickSort(int, int);
    int partition(int, int, int);
    void mergeSort(int, int);
    void merge(int, int);
    void wait();
    void swap(int, int);
    void replace(int, float);

    SortEngineWorker *q_ptr;
    QList<float> m_list;

    int m_sortingAlgorithm;
    int m_operationInterval;
};

#endif // SORTENGINE_P_H
