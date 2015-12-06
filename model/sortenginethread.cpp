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
    m_waitCondition.wakeAll();
}

void SortEngineThread::sleep(int operationInterval)
{
    msleep(operationInterval);
}

SortEngine* SortEngineThread::sortEngine()
{
    return m_engine;
}

void SortEngineThread::run()
{
    exec();
}
