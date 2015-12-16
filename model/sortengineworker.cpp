#include "sortengineworker.h"
#include "sortingalgorithm.h"
#include "algorithms/bubblesort.h"
#include "algorithms/exchangesort.h"
#include "algorithms/selectionsort.h"
#include "algorithms/insertionsort.h"
#include "algorithms/shellsort.h"
#include "algorithms/mergesort.h"
#include "algorithms/quicksort.h"
#include "sortengine.h"
#include "constants.h"

#include <QDebug>

SortEngineWorker::SortEngineWorker()
  : m_algorithm(new QuickSort(this))
{
}

void SortEngineWorker::moveToThread(SortEngine *sortEngine)
{
    m_engine = sortEngine;
    QObject::moveToThread(sortEngine);
}

void SortEngineWorker::sort()
{
    if (!m_engine) {
        qWarning() << Q_FUNC_INFO << " - SortEngine not set for SortEngineWorker. Unable to sort.";
        return;
    }

    m_algorithm->sort();
    emit sorted();
}

void SortEngineWorker::setList(const QList<float> &list)
{
    m_algorithm->m_list = list;
}

void SortEngineWorker::resume()
{
    m_engine->resume();
}

void SortEngineWorker::doSwap(int index1, int index2)
{
    emit swap(index1, index2);

    if (m_algorithm->m_operationInterval > 0) {
        m_engine->sleep(m_algorithm->m_operationInterval);
    }
    else {
        m_engine->wait();
    }
}

void SortEngineWorker::doReplace(int index, float value)
{
    emit replace(index, value);

    if (m_algorithm->m_operationInterval > 0) {
        m_engine->sleep(m_algorithm->m_operationInterval);
    } else {
        m_engine->wait();
    }
}

int SortEngineWorker::sortingAlgorithm()
{
    return m_algorithm->m_sortingAlgorithm;
}

void SortEngineWorker::setSortingAlgorithm(int sortingAlgorithm)
{
    switch (sortingAlgorithm) {
    case KBubbleSort:
        m_algorithm.reset(new BubbleSort(this));
        break;

    case KExchangeSort:
        m_algorithm.reset(new ExchangeSort(this));
        break;

    case KSelectionSort:
        m_algorithm.reset(new SelectionSort(this));
        break;

    case KInsertionSort:
        m_algorithm.reset(new InsertionSort(this));
        break;

    case KShellSort:
        m_algorithm.reset(new ShellSort(this));
        break;

    case KMergeSort:
        m_algorithm.reset(new MergeSort(this));
        break;

    case KQuickSort:
        m_algorithm.reset(new QuickSort(this));
        break;

    default:
        break;
    }

    m_algorithm->m_sortingAlgorithm = sortingAlgorithm;
}

int SortEngineWorker::operationInterval()
{
    return m_algorithm->m_operationInterval;
}

void SortEngineWorker::setOperationInterval(int operationInterval)
{
    m_algorithm->m_operationInterval = operationInterval;
}
