#include "sortenginethread.h"
#include "sortengine.h"
#include <QDebug>

SortEngineThread::SortEngineThread(QObject *parent)
    : QThread(parent)
    , mEngine(new SortEngine())
    , mOperationInterval(200)
{
    start();
    setPriority(QThread::HighestPriority);
    mEngine->moveToThread(this);

    connect(this, SIGNAL(finished()), mEngine, SLOT(deleteLater()));
    connect(this, SIGNAL(finished()), this, SLOT(deleteLater()));
}

SortEngineThread::~SortEngineThread()
{
}

SortEngine* SortEngineThread::sortEngine()
{
    return mEngine;
}

void SortEngineThread::wait()
{
    lock.lock();
    mwaitCondition.wait(&lock);
    lock.unlock();
}

void SortEngineThread::resume()
{
    mwaitCondition.wakeAll();
}

void SortEngineThread::sleep(int operationInterval)
{
    msleep(operationInterval);
}
