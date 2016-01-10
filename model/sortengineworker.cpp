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
  // std::make_unique not yet available.
  : m_algorithm(new QuickSort(this))
{
}

void SortEngineWorker::setSortEngine(SortEngine *sortEngine)
{
    m_engine = sortEngine;
    moveToThread(m_engine);
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
    m_algorithm->setList(list);
}

void SortEngineWorker::resume()
{
    m_engine->resume();
}

void SortEngineWorker::doSwap(int index1, int index2)
{
    emit swap(index1, index2);

    m_engine->wait();
}

void SortEngineWorker::doReplace(int index, float value)
{
    emit replace(index, value);

    m_engine->wait();
}

Algorithm SortEngineWorker::sortingAlgorithm()
{
    return m_algorithm->sortingAlgorithm();
}

void SortEngineWorker::setSortingAlgorithm(Algorithm sortingAlgorithm)
{
    switch (sortingAlgorithm) {
    case Algorithm::BubbleSort:
        m_algorithm.reset(new BubbleSort(this));
        break;

    case Algorithm::ExchangeSort:
        m_algorithm.reset(new ExchangeSort(this));
        break;

    case Algorithm::InsertionSort:
        m_algorithm.reset(new InsertionSort(this));
        break;

    case Algorithm::MergeSort:
        m_algorithm.reset(new MergeSort(this));
        break;

    case Algorithm::SelectionSort:
        m_algorithm.reset(new SelectionSort(this));
        break;

    case Algorithm::ShellSort:
        m_algorithm.reset(new ShellSort(this));
        break;

    case Algorithm::QuickSort:
        m_algorithm.reset(new QuickSort(this));
        break;

    default:
        break;
    }
}
