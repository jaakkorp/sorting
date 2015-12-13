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

    void setThread(SortEngineThread *thread);
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
    SortEngineThread *m_engineThread;
    SortEnginePrivate *d_ptr;

private:
    Q_DECLARE_PRIVATE(SortEngine)
};

Q_DECLARE_METATYPE(SortEngine*)

#endif // SORTENGINE_H
