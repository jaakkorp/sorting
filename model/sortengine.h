#ifndef SORTENGINETHREAD_H
#define SORTENGINETHREAD_H

#include <QThread>
#include <QMutex>
#include <QWaitCondition>

class SortEngineWorker;

class SortEngine : public QThread
{
    Q_OBJECT

public:
    SortEngine(QObject *parent = 0);

    Q_INVOKABLE void wait();
    Q_INVOKABLE void resume();
    Q_INVOKABLE void sleep(int operationInterval);
    void setList(const QList<float> &list);
    int sortingAlgorithm();
    void setSortingAlgorithm(int sortingAlgorithm);
    int operationInterval();
    void setOperationInterval(int operationInterval);
    void sort();

signals:
    void swap(int index1, int index2);
    void replace(int index, float value);
    void sorted();

protected:
    virtual void run();

private:
    Q_INVOKABLE void doResume();

private:
    QMutex m_lock;
    QWaitCondition m_waitCondition;
    SortEngineWorker *m_worker;
    int m_operationInterval;
};

#endif // SORTENGINETHREAD_H

