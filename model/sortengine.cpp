#include "sortengine.h"
#include "sortengine_p.h"
#include "sortenginethread.h"
#include "constants.h"

#include <QDebug>

SortEngine::SortEngine()
  : d_ptr(new SortEnginePrivate(this))
{
}

SortEngine::~SortEngine()
{
}

void SortEngine::moveToThread(QThread *thread)
{
    mEngineThread = qobject_cast<SortEngineThread*>(thread);
    QObject::moveToThread(thread);
}

void SortEngine::sort()
{
    Q_D(SortEngine);

    if (!mEngineThread) {
        qWarning() << Q_FUNC_INFO << " - SortEngineThread not set for SortEngine. Unable to sort.";
        return;
    }

    d->sort();
    emit sorted();
}

void SortEngine::setList(QList<float> &list)
{
    Q_D(SortEngine);

    d->mList = list;
}

void SortEngine::resume()
{
    mEngineThread->resume();
}

void SortEngine::doSwap(int index1, int index2)
{
    Q_D(SortEngine);

    emit swap(index1, index2);

    if (d->mOperationInterval > 0)
        mEngineThread->sleep(d->mOperationInterval);
    else
        mEngineThread->wait();
}

void SortEngine::doReplace(int index, float value)
{
    Q_D(SortEngine);

    emit replace(index, value);

    if (d->mOperationInterval > 0)
        mEngineThread->sleep(d->mOperationInterval);
    else
        mEngineThread->wait();
}

int SortEngine::sortingAlgorithm()
{
    Q_D(SortEngine);

    return d->mSortingAlgorithm;
}

void SortEngine::setSortingAlgorithm(int sortingAlgorithm)
{
    Q_D(SortEngine);

    d->mSortingAlgorithm = sortingAlgorithm;
}

int SortEngine::operationInterval()
{
    Q_D(SortEngine);

    return d->mOperationInterval;
}

void SortEngine::setOperationInterval(int operationInterval)
{
    Q_D(SortEngine);

    d->mOperationInterval = operationInterval;
}
