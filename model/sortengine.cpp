#include "sortengine.h"
#include "sortengineworker.h"
#include <QMutexLocker>

SortEngine::SortEngine(QObject *parent)
    : QThread(parent)
    , m_worker(new SortEngineWorker())
{
    qRegisterMetaType<QList<float>>("QList<float>");

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

Algorithm SortEngine::sortingAlgorithm()
{
    return m_worker->sortingAlgorithm();
}

void SortEngine::setSortingAlgorithm(Algorithm sortingAlgorithm)
{
    m_worker->setSortingAlgorithm(sortingAlgorithm);
}

void SortEngine::sort(const QList<float> &list)
{
    QMetaObject::invokeMethod(m_worker, "sort", Qt::AutoConnection, Q_ARG(QList<float>, list));
}

void SortEngine::run()
{
    exec();
}

void SortEngine::doResume()
{
    m_waitCondition.wakeAll();
}
