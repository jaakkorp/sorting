#include "sortboxmodel.h"
#include "sortenginefactory.h"
#include "sortenginethread.h"
#include "sortengine.h"
#include "constants.h"

#include <QThread>
#include <QMetaObject>
#include <QDebug>

const float KFirstBarHeightRatio = 0.05f;
const float KLastBarHeightRatio = 0.95f;

SortBoxModel::SortBoxModel(QObject *parent)
    : QAbstractListModel(parent)
    , m_size(12)
    , m_sorting(false)
    , m_sorted(false)
    , m_operationCount(0)
{
    qRegisterMetaType<SortEngine*>("SortEngine *");

    m_engineThread = new SortEngineThread();

    connect(m_engineThread, &SortEngineThread::swap, this, &SortBoxModel::swap);
    connect(m_engineThread, &SortEngineThread::replace, this, &SortBoxModel::replace);
    connect(m_engineThread, &SortEngineThread::sorted, this, &SortBoxModel::listSorted);
    connect(this, &QObject::destroyed, m_engineThread, &QThread::quit);

    auto heightRatioIncrease = (KLastBarHeightRatio - KFirstBarHeightRatio) / (m_size - 1);
    auto barHeightRatio = KFirstBarHeightRatio;

    for (auto i(0); i < m_size; ++i) {
        m_barHeights.append(barHeightRatio);
        barHeightRatio += heightRatioIncrease;
    }

    scramble();
}

QHash<int, QByteArray> SortBoxModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[BarHeightRatioRole] = "barHeightRatio";

    return roles;
}

QVariant SortBoxModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole && role != BarHeightRatioRole)
        return QVariant();

    if (role == Qt::DisplayRole)
        return "";
    else
        return m_barHeights.at(index.row());
}

int SortBoxModel::rowCount(const QModelIndex &/*parent*/) const
{
    return m_barHeights.count();
}

SortBoxModel::SortingAlgorithm SortBoxModel::sortingAlgorithm()
{
    return toSortingEnum(m_engineThread->sortingAlgorithm());
}

void SortBoxModel::setSortingAlgorithm(SortBoxModel::SortingAlgorithm sortingAlgorithm)
{
    if (sortingAlgorithm != toSortingEnum(m_engineThread->sortingAlgorithm())) {
        m_engineThread->setSortingAlgorithm(toSortingConstInt(sortingAlgorithm));
        emit sortingAlgorithmChanged();
    }
}

int SortBoxModel::size() const
{
    return m_barHeights.size();
}

void SortBoxModel::setSize(int size)
{
    if (size > 0 && size != m_barHeights.size()) {
        m_size = size;
        repopulate();

        emit sizeChanged();
    }
}

int SortBoxModel::count() const
{
    return m_barHeights.count();
}

bool SortBoxModel::sorting() const
{
    return m_sorting;
}

bool SortBoxModel::sorted() const
{
    return m_sorted;
}

void SortBoxModel::setSorted(bool sorted)
{
    if (sorted || !m_sorted || m_sorting)
        return;

    m_sorted = false;

    emit sortedChanged();
}

int SortBoxModel::operationCount() const
{
    return m_operationCount;
}

int SortBoxModel::operationInterval() const
{
    return m_engineThread->operationInterval();
}

void SortBoxModel::setOperationInterval(int operationInterval)
{
    if (operationInterval != m_engineThread->operationInterval()) {
        m_engineThread->setOperationInterval(operationInterval);

        emit operationIntervalChanged();
    }
}

void SortBoxModel::sort()
{
    m_engineThread->setList(m_barHeights);
    m_engineThread->sort();
    m_sorting = true;
    m_operationCount = 0;

    emit sortingChanged();
    emit operationCountChanged();
}

void SortBoxModel::move(int from, int to)
{
    m_barHeights.move(from, to);

    emit dataChanged(index(from), index(from));
    emit dataChanged(index(to), index(to));
}

void SortBoxModel::scramble()
{
    m_sorted = false;

    for (auto i(0); i < m_barHeights.count() * 2; ++i) {
        auto index1 = rand() % m_barHeights.count();
        auto index2 = rand() % m_barHeights.count();

        while (index1 == index2)
            index2 = rand() % m_barHeights.count();

        m_barHeights.swap(index1, index2);
    }

    emit sortedChanged();
    emit dataChanged(index(0), index(m_barHeights.count() - 1));
}

QVariantList SortBoxModel::randomOrder(int itemCount)
{
    auto heightRatioIncrease = (KLastBarHeightRatio - KFirstBarHeightRatio) / (itemCount - 1);
    auto barHeightRatio = KFirstBarHeightRatio;

    QVariantList list;

    for (auto i(0); i < itemCount; ++i) {
        list.append(barHeightRatio);
        barHeightRatio += heightRatioIncrease;
    }

    for (auto i(0); i < itemCount * 2; ++i) {
        auto index1 = rand() % list.count();
        auto index2 = rand() % list.count();

        while (index1 == index2)
            index2 = rand() % list.count();

        list.swap(index1, index2);
    }

    return list;
}

QVariantList SortBoxModel::reverseOrder(int itemCount)
{
    auto heightRatioIncrease = (KLastBarHeightRatio - KFirstBarHeightRatio) / (itemCount - 1);
    auto barHeightRatio = KFirstBarHeightRatio;

    QVariantList list;

    for (auto i(0); i < itemCount; ++i) {
        list.prepend(barHeightRatio);
        barHeightRatio += heightRatioIncrease;
    }

    return list;
}

void SortBoxModel::setOrder(const QVariantList &list)
{
    if (list.count() < 1 || sorting())
        return;

    m_barHeights.clear();

    for (int i(0); i < list.count(); i++)
        m_barHeights.append(list[i].toReal());

    m_sorted = false;
    emit sortedChanged();
    emit dataChanged(index(0), index(m_barHeights.count() - 1));
}

void SortBoxModel::swap(int index1, int index2)
{
    m_barHeights.swap(index1, index2);
    ++m_operationCount;

    emit operationCountChanged();

    if (index1 < index2) {
        emit dataChanged(index(index1), index(index2));
    } else {
        emit dataChanged(index(index2), index(index1));
    }
}

void SortBoxModel::replace(int itemIndex, float value)
{
    // TODO: check marge sort algorithm. Right now we are asked to replace
    // a value with the same value and the logic depends on values changing
    // (SortBox.qml: onMovingChanged in Bar delegate).
    auto old = m_barHeights[itemIndex];
    if (value == old) {
        proceed();
        return;
    }

    m_barHeights.replace(itemIndex, value);
    ++m_operationCount;

    emit operationCountChanged();
    emit dataChanged(index(itemIndex), index(itemIndex));
}

void SortBoxModel::listSorted()
{
    m_sorting = false;
    m_sorted = true;

    emit sortedChanged();
    emit sortingChanged();
}

void SortBoxModel::proceed()
{
    m_engineThread->resume();

}

void SortBoxModel::repopulate()
{
    auto heightRatioIncrease = (KLastBarHeightRatio - KFirstBarHeightRatio) / (m_size - 1);
    auto barHeightRatio = KFirstBarHeightRatio;

    m_barHeights.clear();

    for (auto i(0); i < m_size; ++i) {
        m_barHeights.append(barHeightRatio);
        barHeightRatio += heightRatioIncrease;
    }

    scramble();

    emit dataChanged(index(0), index(m_barHeights.count() - 1));
}

int SortBoxModel::toSortingConstInt(SortBoxModel::SortingAlgorithm sortingAlgorithm)
{
    switch (sortingAlgorithm) {
    case SortBoxModel::BubbleSort:
        return KBubbleSort;

    case SortBoxModel::ExchangeSort:
        return KExchangeSort;

    case SortBoxModel::SelectionSort:
        return KSelectionSort;

    case SortBoxModel::InsertionSort:
        return KInsertionSort;

    case SortBoxModel::ShellSort:
        return KShellSort;

    case SortBoxModel::MergeSort:
        return KMergeSort;

    case SortBoxModel::QuickSort:
        return KQuickSort;

    default:
        return -1;
    }
}

SortBoxModel::SortingAlgorithm SortBoxModel::toSortingEnum(int sortingAlgorithm)
{
    switch (sortingAlgorithm) {
    case KBubbleSort:
        return SortBoxModel::BubbleSort;

    case KExchangeSort:
        return SortBoxModel::ExchangeSort;

    case KSelectionSort:
        return SortBoxModel::SelectionSort;

    case KInsertionSort:
        return SortBoxModel::InsertionSort;

    case KShellSort:
        return SortBoxModel::ShellSort;

    case KMergeSort:
        return SortBoxModel::MergeSort;

    case KQuickSort:
        return SortBoxModel::QuickSort;

    default:
        return SortBoxModel::Undefined;
    }
}
