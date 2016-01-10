#ifndef CONSTANTS_H
#define CONSTANTS_H

enum class Algorithm
{
    Undefined = -1,
    BubbleSort,
    ExchangeSort,
    InsertionSort,
    MergeSort,
    SelectionSort,
    ShellSort,
    QuickSort
};

const int KBubbleSort = static_cast<int>(Algorithm::BubbleSort);
const int KExchangeSort = static_cast<int>(Algorithm::ExchangeSort);
const int KInsertionSort = static_cast<int>(Algorithm::InsertionSort);
const int KMergeSort = static_cast<int>(Algorithm::MergeSort);
const int KSelectionSort = static_cast<int>(Algorithm::SelectionSort);
const int KShellSort = static_cast<int>(Algorithm::ShellSort);
const int KQuickSort = static_cast<int>(Algorithm::QuickSort);

#endif // CONSTANTS_H
