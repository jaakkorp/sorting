#ifndef SORTENGINEWORKER_H
#define SORTENGINEWORKER_H

#include <QObject>
#include <QMetaType>

class SortEngine;
class SortEngineWorkerPrivate;

class SortEngineWorker : public QObject
{
    Q_OBJECT

public:
    explicit SortEngineWorker();

    void setThread(SortEngineWorker *thread);
    void setList(const QList<float> &list);
    int sortingAlgorithm();
    void setSortingAlgorithm(int sortingAlgorithm);
    int operationInterval();
    void setOperationInterval(int operationInterval);
    void moveToThread(QThread *thread);
    Q_INVOKABLE void sort();
    Q_INVOKABLE void resume();

signals:
    void swap(int index1, int index2);
    void replace(int index, float value);
    void sorted();

private:
    void doSwap(int index1, int index2);
    void doReplace(int index, float value);
    void wait();

protected:
    SortEngine *m_engine;
    SortEngineWorkerPrivate *d_ptr;

private:
    Q_DECLARE_PRIVATE(SortEngineWorker)
};

Q_DECLARE_METATYPE(SortEngineWorker*)

#endif // SORTENGINEWORKER_H
