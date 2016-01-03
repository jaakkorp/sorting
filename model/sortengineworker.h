#ifndef SORTENGINEWORKER_H
#define SORTENGINEWORKER_H

#include "sortingalgorithm.h"
#include <QObject>
#include <QMetaType>
#include <memory>

class SortEngine;
class SortingAlgorithm;

class SortEngineWorker : public QObject
{
    Q_OBJECT

public:
    explicit SortEngineWorker();

    void setList(const QList<float> &list);
    int sortingAlgorithm();
    void setSortingAlgorithm(int sortingAlgorithm);
    void moveToThread(SortEngine *sortEngine);
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
    std::unique_ptr<SortingAlgorithm> m_algorithm;

    friend class SortingAlgorithm;
};

Q_DECLARE_METATYPE(SortEngineWorker*)

#endif // SORTENGINEWORKER_H
