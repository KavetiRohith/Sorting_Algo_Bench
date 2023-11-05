#include <functional>
#include <vector>
#include <chrono>
#include <map>
#include <unordered_set>
#include <random>

#include "bench.h"
#include "sorting_algorithms.h"
#include "matplotlib-cpp/matplotlibcpp.h"

#define PRINT_GENERATED_ARRAYS 0

using namespace std;

namespace plt = matplotlibcpp;

const int BENCH_ITERATIONS = 5;
const int RAND_GEN_LOW = 0;
const int RAND_GEN_HIGH = 50000;

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
#if PRINT_GENERATED_ARRAYS
    cout << "genRandom Array: "
         << "size: " << size << endl;
    printArray(arr, size);
#endif
}

void print_durations_best_avg_worst_cases(const vector<pair<string, array<double, 3>>> &durations_vec)
{
    for (const auto &pair : durations_vec)
    {
        cout << pair.first << endl;
        cout << "random array: " << pair.second[0] << endl;
        cout << "sorted array: " << pair.second[1] << endl;
        cout << "sorted array(desc): " << pair.second[2] << endl
             << endl;
    }
}

void bench_best_avg_worst_cases()
{
    int ARRAY_SIZE = 10000;
    int arr[ARRAY_SIZE];
    genRandom(arr, ARRAY_SIZE);

    vector<pair<string, array<double, 3>>> durations_vec;

    bench_cases_helper("MergeSort", MergeSort, arr, ARRAY_SIZE, durations_vec);
    bench_cases_helper("BubbleSort", bubbleSort, arr, ARRAY_SIZE, durations_vec);
    bench_cases_helper("SelectionSort", selectionSort, arr, ARRAY_SIZE, durations_vec);
    bench_cases_helper("InsertionSort", insertionSort, arr, ARRAY_SIZE, durations_vec);
    bench_cases_helper("QuickSort-RandomPivot", quickSortRandomPivot, arr, ARRAY_SIZE, durations_vec);
    bench_cases_helper("QuickSort-MedianOfMedians", quickSortMedianOfMedians, arr, ARRAY_SIZE, durations_vec);
    bench_cases_helper("QuickSort-FirstElementAsPivot", quickSortFirstElementAsPivot, arr, ARRAY_SIZE, durations_vec);

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

    plt::ylabel("Time Taken (seconds)");
    plt::legend();

    print_durations_best_avg_worst_cases(durations_vec);

    // Save the image (file format is determi-ned by the extension)
    plt::save("./Out.jpg");
}

void bench_algorithms_variable_array_sizes(map<string, vector<pair<int, double>>> &durations)
{
    durations["MergeSort"] = {};
    durations["BubbleSort"] = {};
    durations["SelectionSort"] = {};
    durations["InsertionSort"] = {};
    durations["QuickSort-RandomPivot"] = {};
    durations["QuickSort-MedianOfMedians"] = {};
    durations["QuickSort-FirstElementAsPivot"] = {};

    for (int arr_size = 1000; arr_size <= 10000; arr_size += 1000)
    {
        int arr[arr_size];
        genRandom(arr, arr_size);

        auto duration = bench_helper(arr, arr_size, MergeSort);
        durations["MergeSort"].push_back(make_pair(arr_size, duration));

        duration = bench_helper(arr, arr_size, bubbleSort);
        durations["BubbleSort"].push_back(make_pair(arr_size, duration));

        duration = bench_helper(arr, arr_size, selectionSort);
        durations["SelectionSort"].push_back(make_pair(arr_size, duration));

        duration = bench_helper(arr, arr_size, insertionSort);
        durations["InsertionSort"].push_back(make_pair(arr_size, duration));

        duration = bench_helper(arr, arr_size, quickSortRandomPivot);
        durations["QuickSort-RandomPivot"].push_back(make_pair(arr_size, duration));

        duration = bench_helper(arr, arr_size, quickSortMedianOfMedians);
        durations["QuickSort-MedianOfMedians"].push_back(make_pair(arr_size, duration));

        duration = bench_helper(arr, arr_size, quickSortFirstElementAsPivot);
        durations["QuickSort-FirstElementAsPivot"].push_back(make_pair(arr_size, duration));
    }
}

void print_time_for_array_multiple_sizes(const map<string, vector<pair<int, double>>> &durations)
{
    for (const auto &algo_durations_pair : durations)
    {
        cout << algo_durations_pair.first << endl;
        for (const auto &size_time_pair : algo_durations_pair.second)
        {
            cout << "size: " << size_time_pair.first << " : " << size_time_pair.second << " seconds" << endl;
        }
        cout << endl;
    }
}

void bench_algorithms_variable_array_sizes()
{
    map<string, vector<pair<int, double>>> durations;
    bench_algorithms_variable_array_sizes(durations);

    plt::figure_size(1280, 720);

    for (const auto &itr : durations)
    {
        string algorithm = itr.first;
        auto size_duration_pairs = itr.second;

        vector<int> sizes;
        vector<double> times;

        for (const auto &size_duration_pair : size_duration_pairs)
        {
            sizes.push_back(size_duration_pair.first);
            times.push_back(size_duration_pair.second);
        }

        plt::named_plot(algorithm, sizes, times);
        plt::xticks(sizes);
    }

    plt::ylabel("Time Taken (seconds)");
    plt::xlabel("Array Size");
    plt::legend();

    print_time_for_array_multiple_sizes(durations);

    // Save the image (file format is determined by the extension)
    plt::save("./Out-sizes.jpg");
}
