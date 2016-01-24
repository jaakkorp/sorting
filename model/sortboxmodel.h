#ifndef SORTBOXMODEL_H
#define SORTBOXMODEL_H

#include "sortengine.h"
#include "constants.h"
#include <QAbstractListModel>

QT_USE_NAMESPACE

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

public:
    enum ItemRole {
        BarHeightRatioRole = Qt::UserRole + 1
    };

    // For exposing to QML.
    enum class SortingAlgorithm {
        Undefined = static_cast<int>(Algorithm::Undefined),
        BubbleSort = static_cast<int>(Algorithm::BubbleSort),
        ExchangeSort = static_cast<int>(Algorithm::ExchangeSort),
        InsertionSort = static_cast<int>(Algorithm::InsertionSort),
        MergeSort = static_cast<int>(Algorithm::MergeSort),
        SelectionSort = static_cast<int>(Algorithm::SelectionSort),
        ShellSort = static_cast<int>(Algorithm::ShellSort),
        QuickSort = static_cast<int>(Algorithm::QuickSort)
    };

    Q_ENUM(SortingAlgorithm)

    SortBoxModel(QObject *parent = 0);

    QVariant data(const QModelIndex &index, int role) const;
    int rowCount(const QModelIndex &parent) const;

    SortingAlgorithm sortingAlgorithm();
    void setSortingAlgorithm(SortingAlgorithm sortingAlgorithm);
    int size() const;
    void setSize(int size);
    int count() const;
    bool sorting() const;
    bool sorted() const;
    void setSorted(bool sorted);
    int operationCount() const;
    void swap(int index1, int index2);
    void replace(int itemIndex, float value);
    void listSorted();

    Q_INVOKABLE void sort();
    Q_INVOKABLE void move(int from, int to);
    Q_INVOKABLE void scramble();
    Q_INVOKABLE void setOrder(const QVariantList &list);
    Q_INVOKABLE void proceed();
    Q_INVOKABLE QVariantList randomOrder(int itemCount) const;
    Q_INVOKABLE QVariantList reverseOrder(int itemCount) const;
    Q_INVOKABLE QStringList algorithms() const;

signals:
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
    int toSortingConstInt(Algorithm sortingAlgorithm);
    Algorithm toAlgorithmEnum(int sortingAlgorithm);

private:
    SortEngine *m_engine;
    int m_size;
    bool m_sorting;
    bool m_sorted;
    int m_operationCount;
    QList<float> m_barHeights;
};

#endif // SORTBOXMODEL_H
