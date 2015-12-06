#ifndef SORTENGINE_P_H
#define SORTENGINE_P_H

#include <QList>

class SortEngine;

class SortEnginePrivate
{
    Q_DECLARE_PUBLIC(SortEngine)

public:
    SortEnginePrivate(SortEngine *q);

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

    SortEngine *q_ptr;
    QList<float> m_list;

    int m_sortingAlgorithm;
    int m_operationInterval;
};

#endif // SORTENGINE_P_H
