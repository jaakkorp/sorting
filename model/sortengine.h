#ifndef SORTENGINETHREAD_H
#define SORTENGINETHREAD_H

#include <QThread>
#include <QMutex>
#include <QWaitCondition>

class SortEngineWorker;
enum class Algorithm;

class SortEngine : public QThread
{
    Q_OBJECT

public:
    SortEngine(QObject *parent = 0);

    Q_INVOKABLE void wait();
    Q_INVOKABLE void resume();
    Algorithm sortingAlgorithm();
    void setSortingAlgorithm(Algorithm sortingAlgorithm);
    void sort(const QList<float> &list);

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
};

#endif // SORTENGINETHREAD_H

