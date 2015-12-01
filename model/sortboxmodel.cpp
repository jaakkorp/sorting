#include "sortboxmodel.h"
#include "sortenginefactory.h"
#include "sortenginethread.h"
#include "sortengine.h"
#include "constants.h"

//#include <math.h>
#include <QThread>
#include <QMetaObject>
#include <QDebug>

const float KFirstBarHeightRatio = 0.05f;
const float KLastBarHeightRatio = 0.95f;

SortBoxModel::SortBoxModel(QObject *parent)
    : QAbstractListModel(parent)
    , mSize(12)
    , mSorting(false)
    , mSorted(false)
{
    qRegisterMetaType<SortEngine*>("SortEngine*");
    mEngineThread = new SortEngineThread();
    mEngine = mEngineThread->sortEngine();
    connect(mEngine, SIGNAL(swap(int, int)), this, SLOT(swap(int, int)));
    connect(mEngine, SIGNAL(replace(int, float)), this, SLOT(replace(int, float)));
    connect(mEngine, SIGNAL(sorted()), this, SLOT(listSorted()));
    connect(this, SIGNAL(destroyed()), mEngineThread, SLOT(quit()));

    float heightRatioIncrease = (KLastBarHeightRatio - KFirstBarHeightRatio) / (mSize - 1);
    float barHeightRatio = KFirstBarHeightRatio;

    for (int i(0); i < mSize; i++) {
        mBarHeights.append(barHeightRatio);
        barHeightRatio += heightRatioIncrease;
    }

    scramble();
}

SortBoxModel::~SortBoxModel()
{
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
        return mBarHeights.at(index.row());
}

int SortBoxModel::rowCount(const QModelIndex &/*parent*/) const
{
    return mBarHeights.count();
}

void SortBoxModel::sort()
{
    mEngine->setList(mBarHeights);
    QMetaObject::invokeMethod(mEngine, "sort");
    mSorting = true;
    mOperationCount = 0;
    emit sortingChanged();
    emit operationCountChanged();
}

SortBoxModel::SortingAlgorithm SortBoxModel::sortingAlgorithm()
{
    return toSortingEnum(mEngine->sortingAlgorithm());
}

void SortBoxModel::setSortingAlgorithm(SortBoxModel::SortingAlgorithm sortingAlgorithm)
{
    if (sortingAlgorithm != toSortingEnum(mEngine->sortingAlgorithm())) {
        mEngine->setSortingAlgorithm(toSortingConstInt(sortingAlgorithm));
        emit sortingAlgorithmChanged();
    }
}

int SortBoxModel::size() const
{
    return mBarHeights.size();
}

void SortBoxModel::setSize(int size)
{
    if (size > 0 && size != mBarHeights.size()) {
        mSize = size;
        repopulate();
        emit sizeChanged();
    }
}

int SortBoxModel::count() const
{
    return mBarHeights.count();
}

bool SortBoxModel::sorting() const
{
    return mSorting;
}

bool SortBoxModel::sorted() const
{
    return mSorted;
}

void SortBoxModel::setSorted(bool sorted)
{
    if (sorted || !mSorted || mSorting)
        return;

    mSorted = false;
    emit sortedChanged();
}

int SortBoxModel::operationCount() const
{
    return mOperationCount;
}

int SortBoxModel::operationInterval() const
{
    return mEngine->operationInterval();
}

void SortBoxModel::setOperationInterval(int operationInterval)
{
    if (operationInterval != mEngine->operationInterval()) {
        mEngine->setOperationInterval(operationInterval);
        emit operationIntervalChanged();
    }
}

void SortBoxModel::move(int from, int to)
{
    mBarHeights.move(from, to);
    emit dataChanged(index(from), index(from));
    emit dataChanged(index(to), index(to));
}

void SortBoxModel::repopulate()
{
    float heightRatioIncrease = (KLastBarHeightRatio - KFirstBarHeightRatio) / (mSize - 1);
    float barHeightRatio = KFirstBarHeightRatio;

    mBarHeights.clear();
    for (int i(0); i < mSize; i++) {
        mBarHeights.append(barHeightRatio);
        barHeightRatio += heightRatioIncrease;
    }

    scramble();

    emit dataChanged(this->index(0), this->index(mBarHeights.count() - 1));
}

void SortBoxModel::scramble()
{
    for (int i(0); i < mBarHeights.count() * 2; i++) {
        int index1 = rand() % mBarHeights.count();
        int index2 = rand() % mBarHeights.count();
        while (index1 == index2)
            index2 = rand() % mBarHeights.count();
        mBarHeights.swap(index1, index2);
    }
    mSorted = false;
    emit sortedChanged();
    emit dataChanged(index(0), index(mBarHeights.count() - 1));
}

QVariantList SortBoxModel::randomOrder(int itemCount)
{
    float heightRatioIncrease = (KLastBarHeightRatio - KFirstBarHeightRatio) / (itemCount - 1);
    float barHeightRatio = KFirstBarHeightRatio;

    QVariantList list;

    for (int i(0); i < itemCount; i++) {
        list.append(barHeightRatio);
        barHeightRatio += heightRatioIncrease;
    }

    for (int i(0); i < itemCount * 2; i++) {
        int index1 = rand() % list.count();
        int index2 = rand() % list.count();
        while (index1 == index2)
            index2 = rand() % list.count();

        list.swap(index1, index2);
    }

    return list;
}

QVariantList SortBoxModel::reverseOrder(int itemCount)
{
    float heightRatioIncrease = (KLastBarHeightRatio - KFirstBarHeightRatio) / (itemCount - 1);
    float barHeightRatio = KFirstBarHeightRatio;

    QVariantList list;

    for (int i(0); i < itemCount; i++) {
        list.prepend(barHeightRatio);
        barHeightRatio += heightRatioIncrease;
    }

    return list;
}

void SortBoxModel::setOrder(QVariantList list)
{
    if (list.count() < 1 || sorting())
        return;

    mBarHeights.clear();

    for (int i(0); i < list.count(); i++)
        mBarHeights.append(list[i].toReal());

    mSorted = false;
    emit sortedChanged();
    emit dataChanged(index(0), index(mBarHeights.count() - 1));
}

void SortBoxModel::swap(int index1, int index2)
{
    mBarHeights.swap(index1, index2);
    mOperationCount++;
    emit operationCountChanged();
    if (index1 < index2)
        emit dataChanged(index(index1), index(index2));
    else
        emit dataChanged(index(index2), index(index1));
}

void SortBoxModel::replace(int index, float value)
{
    mBarHeights.replace(index, value);
    mOperationCount++;
    emit operationCountChanged();
    emit dataChanged(this->index(index), this->index(index));
}

void SortBoxModel::proceed()
{
    if (!(mEngine->operationInterval() > 0))
        QMetaObject::invokeMethod(mEngineThread, "resume");
}

void SortBoxModel::listSorted()
{
    mSorting = false;
    mSorted = true;
    emit sortedChanged();
    emit sortingChanged();
}

int SortBoxModel::toSortingConstInt(SortBoxModel::SortingAlgorithm algorithm)
{
    switch (algorithm) {
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

SortBoxModel::SortingAlgorithm SortBoxModel::toSortingEnum(int algorithm)
{
    switch (algorithm) {
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
