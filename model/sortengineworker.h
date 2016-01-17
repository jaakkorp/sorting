#ifndef SORTENGINEWORKER_H
#define SORTENGINEWORKER_H

#include "sortingalgorithm.h"
#include <QObject>
#include <QMetaType>
#include <memory>

class SortEngine;
class SortingAlgorithm;
enum class Algorithm;

class SortEngineWorker : public QObject
{
    Q_OBJECT

public:
    explicit SortEngineWorker();

    Algorithm sortingAlgorithm();
    void setSortingAlgorithm(Algorithm sortingAlgorithm);
    void setSortEngine(SortEngine *sortEngine);
    Q_INVOKABLE void sort(const QList<float> &list);
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
