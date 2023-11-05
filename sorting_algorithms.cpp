#include "sorting_algorithms.h"
#include <algorithm>
#include <iostream>
#include <random>

using namespace std;

void selectionSort(int arr[], int n)
{
    int i = -1; // i is keeping track of the start of the sorted array
    while (i < n - 1)
    {
        int bestMinIndexSoFar = i + 1;
        int j = i + 2;
        while (j < n)
        {
            if (arr[j] < arr[bestMinIndexSoFar])
            {
                bestMinIndexSoFar = j;
            }
            j = j + 1;
        }
        // j = n
        int temp = arr[bestMinIndexSoFar];
        arr[bestMinIndexSoFar] = arr[i + 1];
        arr[i + 1] = temp;
        i++;
    }
    // i=n-1
}

void insertionSort(int arr[], int n)
{
    int i = 1;
    while (i < n)
    {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0)
        {
            if (arr[j] > key)
            {
                arr[j + 1] = arr[j];
                j = j - 1;
            }
            else
            {
                break;
            }
        }
        arr[j + 1] = key;
        // j=-1;
        i++;
    }
    // i=n
}

// sliding window of size 2
void bubbleSort(int arr[], int size)
{
    int i = size;
    bool isSwapped = false;
    while (i > 0)
    {
        int j = 0;
        while (j < i - 1)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
                isSwapped = true;
            }

            j++;
        }
        i--;

        if (!isSwapped)
        {
            return;
        }
    }
}

int genPivotAndRearrange(int arr[], int low, int high)
{
    int pivotIndex = rand() % (high - low + 1);
    int pivot = arr[pivotIndex + low];

    int j = low;
    int k = high + 1;
    int i = low;

    while (j < k)
    {
        if (arr[j] == pivot)
        {
            j++;
        }
        else if (arr[j] < pivot)
        {
            swap(arr[i], arr[j]);
            i++;
            j++;
        }
        else
        {
            swap(arr[k - 1], arr[j]);
            k--;
        }
    }

    return i;
}

void quicksort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pivot = genPivotAndRearrange(arr, low, high);
        quicksort(arr, low, pivot - 1);
        quicksort(arr, pivot + 1, high);
    }
}

void quickSortRandomPivot(int arr[], int size)
{
    quicksort(arr, 0, size - 1);
}

void Merge(int arr[], int l[], int lsize, int r[], int rsize)
{
    int i = 0, j = 0, k = 0;
    while (i < lsize && j < rsize)
    {
        if (l[i] <= r[j])
        {
            arr[k] = l[i];
            k++;
            i++;
        }
        else
        {
            arr[k] = r[j];
            j++;
            k++;
        }
    }
    while (i < lsize)
    {
        arr[k] = l[i];
        i++;
        k++;
    }
    while (j < rsize)
    {
        arr[k] = r[j];
        j++;
        k++;
    }
}

void MergeSort(int arr[], int size)
{
    if (size <= 1)
        return;
    int mid = size / 2;
    int l[mid], r[size - mid];
    for (int i = 0; i < mid; i++)
    {
        l[i] = arr[i];
    }
    for (int i = mid; i < size; i++)
    {
        r[i - mid] = arr[i];
    }
    MergeSort(l, mid);
    MergeSort(r, size - mid);
    Merge(arr, l, mid, r, size - mid);
}

// Helper function to find the median of five numbers
int medianOfFive(int arr[], int start)
{
    sort(arr + start, arr + start + 5);
    return arr[start + 2];
}

/*
T(n) = T(n/5) + n
*/
int medianOfMedians(int arr[], int low, int high)
{
    int n = high - low + 1;
    int medians[(n + 4) / 5];
    int i;
    for (i = 0; i < n / 5; i++)
    {
        medians[i] = medianOfFive(arr, low + i * 5);
    }
    if (i * 5 < n)
    {
        sort(arr + low + i * 5, arr + high + 1);
        // medians[i] = arr[low + i * 5 + ((high - (low + i * 5)) / 2)];
        medians[i] = arr[low + i * 5];
        i++;
    }
    if (i == 1)
        return medians[0];
    else
        return medianOfMedians(medians, 0, i - 1);
}

/*
T(n) = n
*/

int partitionWithGivenPivotNew(int arr[], int low, int high, int pivot)
{
    int i = low;
    int j = low;
    int k = high + 1;

    while (j < k)
    {
        if (arr[j] == pivot)
        {
            j++;
        }
        else if (arr[j] < pivot)
        {
            swap(arr[j], arr[i]);
            i++;
            j++;
        }
        else
        {
            swap(arr[k - 1], arr[j]);
            k--;
        }
    }
    return i;
}

/*
T(n) = n + T(3n/10)+T(7n/10)

*/
void quickSortMedianOfMedians(int arr[], int low, int high)
{
    if (low < high)
    {
        int pivotValue = medianOfMedians(arr, low, high);
        int pi = partitionWithGivenPivotNew(arr, low, high, pivotValue);

        quickSortMedianOfMedians(arr, low, pi - 1);
        quickSortMedianOfMedians(arr, pi + 1, high);
    }
}

void quickSortMedianOfMedians(int arr[], int size)
{
    quickSortMedianOfMedians(arr, 0, size - 1);
}

void printArray(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << arr[i] << ",";
    }
    cout << endl
         << endl;
}

bool isSorted(int arr[], int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        if (arr[i] > arr[i + 1])
        {
            return false;
        }
    }

    return true;
}

int genPivotAndRearrangeFirstElementAsPivot(int arr[], int low, int high)
{
    int pivot = arr[low];

    int j = low;
    int k = high + 1;
    int i = low;

    while (j < k)
    {
        if (arr[j] == pivot)
        {
            j++;
        }
        else if (arr[j] < pivot)
        {
            swap(arr[i], arr[j]);
            i++;
            j++;
        }
        else
        {
            swap(arr[k - 1], arr[j]);
            k--;
        }
    }

    return i;
}

void quicksortFirstElementAsPivot(int arr[], int low, int high)
{
    if (low < high)
    {
        int pivot = genPivotAndRearrangeFirstElementAsPivot(arr, low, high);
        quicksortFirstElementAsPivot(arr, low, pivot - 1);
        quicksortFirstElementAsPivot(arr, pivot + 1, high);
    }
}

void quickSortFirstElementAsPivot(int arr[], int size)
{
    quicksortFirstElementAsPivot(arr, 0, size - 1);
}