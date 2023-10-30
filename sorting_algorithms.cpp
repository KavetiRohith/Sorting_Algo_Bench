#include <iostream>
#include <functional>
#include <vector>
#include <chrono>
#include <map>
#include <unordered_set>
#include <random>
#include "matplotlib-cpp/matplotlibcpp.h"
using namespace std;

namespace plt = matplotlibcpp;

const int BENCH_ITERATIONS = 10;
const int RAND_GEN_LOW = 0;
const int RAND_GEN_HIGH = 50000;

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

double bench_helper(int arr[], int size, std::function<void(int[], int)> sorter)
{
    double duration_accumulator;

    for (int i = 0; i < BENCH_ITERATIONS; i++)
    {
        int arr_copy[size];
        for (int i = 0; i < size; i++)
        {
            arr_copy[i] = arr[i];
        }

        auto start = chrono::high_resolution_clock::now();
        sorter(arr_copy, size);
        auto end = chrono::high_resolution_clock::now();

        auto isSortingAlgorithmWorking = isSorted(arr_copy, size);
        if (!isSortingAlgorithmWorking)
        {
            cout << "PANIC !!!";
            exit(1);
        }

        duration_accumulator += chrono::duration_cast<chrono::duration<double>>(end - start).count();
    }

    return duration_accumulator / BENCH_ITERATIONS;
}

void bench_cases_helper(string algorithm_name, std::function<void(int[], int)> sorter, int arr[], int size, vector<pair<string, array<double, 3>>> &durations_vec)
{
    array<double, 3> durations;

    // given input case
    auto duration = bench_helper(arr, size, sorter);
    durations[0] = duration;

    // sorted array case
    int sorted_arr[size];
    for (int i = 0; i < size; i++)
    {
        sorted_arr[i] = arr[i];
    }
    sorter(sorted_arr, size);

    duration = bench_helper(sorted_arr, size, sorter);
    durations[1] = duration;

    // reverse sorted array case
    int reverse_sorted_arr[size];
    int rev_index = 0;
    for (int i = size - 1; i >= 0; i--)
    {
        reverse_sorted_arr[rev_index++] = sorted_arr[i];
    }

    duration = bench_helper(reverse_sorted_arr, size, sorter);
    durations[2] = duration;

    durations_vec.push_back(make_pair(algorithm_name + "-" + to_string(size), durations));
}

void genRandom(int arr[], size_t size)
{
    random_device rd;                                                // Used to seed the random number generator
    mt19937 mt(rd());                                                // Mersenne Twister random number generator
    uniform_int_distribution<int> dist(RAND_GEN_LOW, RAND_GEN_HIGH); // Define the range for the numbers

    unordered_set<int> v;

    while (v.size() != size)
    {
        v.insert(dist(mt));
    }

    // Printing the generated numbers
    int i = 0;
    for (int num : v)
    {
        arr[i++] = num;
    }
}

void bench_cases()
{
    int ARRAY_SIZE = 100;
    int arr[ARRAY_SIZE];
    genRandom(arr, ARRAY_SIZE);

    vector<pair<string, array<double, 3>>> durations_vec;

    bench_cases_helper("BubbleSort", bubbleSort, arr, ARRAY_SIZE, durations_vec);
    bench_cases_helper("MergeSort", MergeSort, arr, ARRAY_SIZE, durations_vec);
    bench_cases_helper("SelectionSort", selectionSort, arr, ARRAY_SIZE, durations_vec);
    bench_cases_helper("InsertionSort", insertionSort, arr, ARRAY_SIZE, durations_vec);
    bench_cases_helper("QuickSort", quickSort, arr, ARRAY_SIZE, durations_vec);

    plt::figure_size(1280, 720);

    for (auto durations : durations_vec)
    {
        vector<double> out;
        vector<string> cases{"random", "sorted ASC", "sorted DESC"};
        vector<int> _cases{1, 2, 3};

        out.assign(durations.second.begin(), durations.second.end());

        plt::xticks(_cases, cases);
        plt::named_plot(durations.first, _cases, out);
    }

    plt::ylabel("Time Taken");
    plt::legend();

    // Save the image (file format is determined by the extension)
    plt::save("./Out.jpg");
}

void bench_individual_algorithms_helper(map<string, vector<pair<int, double>>> &durations)
{
    durations["BubbleSort"] = {};
    durations["MergeSort"] = {};
    durations["SelectionSort"] = {};
    durations["InsertionSort"] = {};
    durations["QuickSort"] = {};

    for (int arr_size = 500; arr_size <= 5000; arr_size += 500)
    {
        int arr[arr_size];
        genRandom(arr, arr_size);

        auto duration = bench_helper(arr, arr_size, bubbleSort);
        durations["BubbleSort"].push_back(make_pair(arr_size, duration));

        duration = bench_helper(arr, arr_size, MergeSort);
        durations["MergeSort"].push_back(make_pair(arr_size, duration));

        duration = bench_helper(arr, arr_size, selectionSort);
        durations["SelectionSort"].push_back(make_pair(arr_size, duration));

        duration = bench_helper(arr, arr_size, insertionSort);
        durations["InsertionSort"].push_back(make_pair(arr_size, duration));

        duration = bench_helper(arr, arr_size, quickSort);
        durations["QuickSort"].push_back(make_pair(arr_size, duration));
    }
}

void bench_individual_algorithms()
{
    map<string, vector<pair<int, double>>> durations;
    bench_individual_algorithms_helper(durations);

    for (const auto &itr : durations)
    {
        plt::figure_size(1280, 720);

        string algorithm = itr.first;
        auto size_duration_pairs = itr.second;

        vector<int> sizes;
        vector<double> times;

        for (const auto &size_duration_pair : size_duration_pairs)
        {
            sizes.push_back(size_duration_pair.first);
            times.push_back(size_duration_pair.second);
        }

        plt::plot(sizes, times);
        plt::ylabel("Time Taken");
        plt::xlabel("Array Size");

        // Save the image (file format is determined by the extension)
        plt::save("./Out-" + algorithm + ".jpg");
    }
}

int main()
{
    bench_cases();
    bench_individual_algorithms();
    return 0;
}