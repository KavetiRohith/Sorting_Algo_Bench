#pragma once
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

void quickSort(int arr[], int size)
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