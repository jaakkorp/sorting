#ifndef SORTENGINE_H
#define SORTENGINE_H

#include <QObject>
#include <QMetaType>

class SortEngineThread;
class SortEnginePrivate;

class SortEngine : public QObject
{
    Q_OBJECT

public:
    explicit SortEngine();
    ~SortEngine();

    void setThread(SortEngineThread *thread);
    void setList(QList<float> &list);
    int sortingAlgorithm();
    void setSortingAlgorithm(int);
    int operationInterval();
    void setOperationInterval(int);
    void moveToThread(QThread *thread);
    Q_INVOKABLE void sort();
    Q_INVOKABLE void resume();

Q_SIGNALS:
    void swap(int, int);
    void replace(int, float);
    void sorted();

private:
    void doSwap(int, int);
    void doReplace(int, float);
    void wait();

protected:
    SortEngineThread *mEngineThread;
    SortEnginePrivate *d_ptr;

private:
    Q_DECLARE_PRIVATE(SortEngine)
};

Q_DECLARE_METATYPE(SortEngine*)

#endif // SORTENGINE_H
