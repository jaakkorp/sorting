#include "sortenginethread.h"
#include "sortengine.h"
#include <QMutexLocker>

SortEngineThread::SortEngineThread(QObject *parent)
    : QThread(parent)
    , m_engine(new SortEngine())
    , m_operationInterval(200)
{
    start();
    m_engine->moveToThread(this);

    connect(m_engine, &SortEngine::swap, this, &SortEngineThread::swap);
    connect(m_engine, &SortEngine::replace, this, &SortEngineThread::replace);
    connect(m_engine, &SortEngine::sorted, this, &SortEngineThread::sorted);

    connect(this, &QThread::finished, m_engine, &QObject::deleteLater);
    connect(this, &QThread::finished, this, &QObject::deleteLater);
}

void SortEngineThread::wait()
{
    QMutexLocker locker(&m_lock);
    m_waitCondition.wait(&m_lock);
}

void SortEngineThread::resume()
{
    if (operationInterval() > 0)
        QMetaObject::invokeMethod(this, "doResume");
}

void SortEngineThread::sleep(int operationInterval)
{
    msleep(operationInterval);
}

SortEngine* SortEngineThread::sortEngine()
{
    return m_engine;
}

void SortEngineThread::setList(const QList<float> &list)
{
    m_engine->setList(list);
}

int SortEngineThread::sortingAlgorithm()
{
    return m_engine->sortingAlgorithm();
}

void SortEngineThread::setSortingAlgorithm(int sortingAlgorithm)
{
    m_engine->setSortingAlgorithm(sortingAlgorithm);
}

int SortEngineThread::operationInterval()
{
    return m_operationInterval;
}

void SortEngineThread::setOperationInterval(int operationInterval)
{
    m_operationInterval = operationInterval;
}

void SortEngineThread::sort()
{
    QMetaObject::invokeMethod(m_engine, "sort");
}

void SortEngineThread::run()
{
    exec();
}

void SortEngineThread::doResume()
{
    m_waitCondition.wakeAll();
}
