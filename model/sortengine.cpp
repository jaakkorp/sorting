#include "sortengine.h"
#include "sortengine_p.h"
#include "sortenginethread.h"
#include "constants.h"

#include <QDebug>

SortEngine::SortEngine()
  : d_ptr(new SortEnginePrivate(this))
{
}

void SortEngine::moveToThread(QThread *thread)
{
    m_engineThread = qobject_cast<SortEngineThread*>(thread);
    QObject::moveToThread(thread);
}

void SortEngine::sort()
{
    Q_D(SortEngine);

    if (!m_engineThread) {
        qWarning() << Q_FUNC_INFO << " - SortEngineThread not set for SortEngine. Unable to sort.";
        return;
    }

    d->sort();
    emit sorted();
}

void SortEngine::setList(QList<float> &list)
{
    Q_D(SortEngine);

    d->m_list = list;
}

void SortEngine::resume()
{
    m_engineThread->resume();
}

void SortEngine::doSwap(int index1, int index2)
{
    Q_D(SortEngine);

    emit swap(index1, index2);

    if (d->m_operationInterval > 0) {
        m_engineThread->sleep(d->m_operationInterval);
    }
    else {
        m_engineThread->wait();
    }
}

void SortEngine::doReplace(int index, float value)
{
    Q_D(SortEngine);

    emit replace(index, value);

    if (d->m_operationInterval > 0) {
        m_engineThread->sleep(d->m_operationInterval);
    } else {
        m_engineThread->wait();
    }
}

int SortEngine::sortingAlgorithm()
{
    Q_D(SortEngine);

    return d->m_sortingAlgorithm;
}

void SortEngine::setSortingAlgorithm(int sortingAlgorithm)
{
    Q_D(SortEngine);

    d->m_sortingAlgorithm = sortingAlgorithm;
}

int SortEngine::operationInterval()
{
    Q_D(SortEngine);

    return d->m_operationInterval;
}

void SortEngine::setOperationInterval(int operationInterval)
{
    Q_D(SortEngine);

    d->m_operationInterval = operationInterval;
}
