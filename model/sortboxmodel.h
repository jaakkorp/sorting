#ifndef SORTBOXMODEL_H
#define SORTBOXMODEL_H

#include "sortengine.h"
#include <QAbstractListModel>

QT_USE_NAMESPACE

class SortEngineThread;
class SortEngine;

class SortBoxModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(SortingAlgorithm sortingAlgorithm READ sortingAlgorithm WRITE setSortingAlgorithm NOTIFY sortingAlgorithmChanged)
    Q_PROPERTY(int size READ size WRITE setSize NOTIFY sizeChanged)
    Q_PROPERTY(int count READ count)
    Q_PROPERTY(bool sorting READ sorting NOTIFY sortingChanged)
    Q_PROPERTY(bool sorted READ sorted WRITE setSorted NOTIFY sortedChanged)
    Q_PROPERTY(int operationCount READ operationCount NOTIFY operationCountChanged)
    Q_PROPERTY(int operationInterval READ operationInterval WRITE setOperationInterval NOTIFY operationIntervalChanged)

    Q_ENUMS(SortingAlgorithm)

public:
    enum ItemRole {
        BarHeightRatioRole = Qt::UserRole + 1
    };

    enum SortingAlgorithm {
        Undefined = -1,
        BubbleSort,
        ExchangeSort,
        SelectionSort,
        InsertionSort,
        ShellSort,
        MergeSort,
        QuickSort
    };

    SortBoxModel(QObject *parent = 0);
    ~SortBoxModel();

    QVariant data(const QModelIndex&, int) const;
    int rowCount(const QModelIndex&) const;

    SortingAlgorithm sortingAlgorithm();
    void setSortingAlgorithm(SortingAlgorithm);
    int size() const;
    void setSize(int);
    int count() const;
    bool sorting() const;
    bool sorted() const;
    void setSorted(bool sorted);
    int operationCount() const;
    int operationInterval() const;
    void setOperationInterval(int operationInterval);

    Q_INVOKABLE void sort();
    Q_INVOKABLE void move(int, int);
    Q_INVOKABLE void scramble();
    Q_INVOKABLE QVariantList randomOrder(int);
    Q_INVOKABLE QVariantList reverseOrder(int);
    Q_INVOKABLE void setOrder(QVariantList);

public Q_SLOTS:
    void swap(int, int);
    void replace(int, float);
    void proceed();
    void listSorted();

Q_SIGNALS:
    void updateReady();
    void sortingAlgorithmChanged();
    void sizeChanged();
    void sortingChanged();
    void sortedChanged();
    void operationCountChanged();
    void operationIntervalChanged();
    void resume();

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    void repopulate();
    int toSortingConstInt(SortingAlgorithm);
    SortingAlgorithm toSortingEnum(int);

    SortEngineThread *mEngineThread;
    SortEngine *mEngine;
    //SortingAlgorithm mSortingAlgorithm;
    int mOperationInterval;
    int mSize;
    bool mSorting;
    bool mSorted;
    int mOperationCount;
    QList<float> mBarHeights;
};

#endif // SORTBOXMODEL_H
