#include "sortengineworker.h"
#include "sortengineworker_p.h"
#include "sortengine.h"
#include "constants.h"

#include <QDebug>

SortEngineWorker::SortEngineWorker()
  : d_ptr(new SortEngineWorkerPrivate(this))
{
}

void SortEngineWorker::moveToThread(QThread *thread)
{
    m_engine = qobject_cast<SortEngine *>(thread);
    QObject::moveToThread(thread);
}

void SortEngineWorker::sort()
{
    Q_D(SortEngineWorker);

    if (!m_engine) {
        qWarning() << Q_FUNC_INFO << " - SortEngine not set for SortEngineWorker. Unable to sort.";
        return;
    }

    d->sort();
    emit sorted();
}

void SortEngineWorker::setList(const QList<float> &list)
{
    Q_D(SortEngineWorker);

    d->m_list = list;
}

void SortEngineWorker::resume()
{
    m_engine->resume();
}

void SortEngineWorker::doSwap(int index1, int index2)
{
    Q_D(SortEngineWorker);

    emit swap(index1, index2);

    if (d->m_operationInterval > 0) {
        m_engine->sleep(d->m_operationInterval);
    }
    else {
        m_engine->wait();
    }
}

void SortEngineWorker::doReplace(int index, float value)
{
    Q_D(SortEngineWorker);

    emit replace(index, value);

    if (d->m_operationInterval > 0) {
        m_engine->sleep(d->m_operationInterval);
    } else {
        m_engine->wait();
    }
}

int SortEngineWorker::sortingAlgorithm()
{
    Q_D(SortEngineWorker);

    return d->m_sortingAlgorithm;
}

void SortEngineWorker::setSortingAlgorithm(int sortingAlgorithm)
{
    Q_D(SortEngineWorker);

    d->m_sortingAlgorithm = sortingAlgorithm;
}

int SortEngineWorker::operationInterval()
{
    Q_D(SortEngineWorker);

    return d->m_operationInterval;
}

void SortEngineWorker::setOperationInterval(int operationInterval)
{
    Q_D(SortEngineWorker);

    d->m_operationInterval = operationInterval;
}
