#include "sortengine.h"
#include "sortengineworker.h"
#include <QMutexLocker>

SortEngine::SortEngine(QObject *parent)
    : QThread(parent)
    , m_worker(new SortEngineWorker())
{
    start();
    m_worker->setSortEngine(this);

    connect(m_worker, &SortEngineWorker::swap, this, &SortEngine::swap);
    connect(m_worker, &SortEngineWorker::replace, this, &SortEngine::replace);
    connect(m_worker, &SortEngineWorker::sorted, this, &SortEngine::sorted);

    connect(this, &QThread::finished, m_worker, &QObject::deleteLater);
    connect(this, &QThread::finished, this, &QObject::deleteLater);
}

void SortEngine::wait()
{
    QMutexLocker locker(&m_lock);
    m_waitCondition.wait(&m_lock);
}

void SortEngine::resume()
{
    QMetaObject::invokeMethod(this, "doResume");
}

void SortEngine::setList(const QList<float> &list)
{
    m_worker->setList(list);
}

int SortEngine::sortingAlgorithm()
{
    return m_worker->sortingAlgorithm();
}

void SortEngine::setSortingAlgorithm(int sortingAlgorithm)
{
    m_worker->setSortingAlgorithm(sortingAlgorithm);
}

void SortEngine::sort()
{
    QMetaObject::invokeMethod(m_worker, "sort");
}

void SortEngine::run()
{
    exec();
}

void SortEngine::doResume()
{
    m_waitCondition.wakeAll();
}
