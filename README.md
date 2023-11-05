# How to run
- **Docker**: if you have docker on your machine run

```sh
    make run-docker 
```

- **Ubuntu 22.04**
```sh
    make setup-ubuntu-focal # installs g++ python3 and python3-matplotlib packages
    make                    # compile
    make run                # generates the plot
```

# Sorting Algorithm Time Complexities

## Sorting Algorithms Comparison when the given array is Unsorted, Sorted in Ascending Order and sorted in Descending Order


![Sorting Algorithms Comparison with an array of size 10000](Out.jpg)


| Sorting Algorithm(Array size: 10000)| Unsorted Array | Sorted Array (Asc) | Sorted Array (Desc) |
|----------------------------|-------------------------|---------------------|---------------------|
| MergeSort                  | 0.0017286               | 0.000758021         | 0.000797441         |
| BubbleSort                 | 0.384094                | 0.00001744          | 0.405408            |
| SelectionSort              | 0.0940289               | 0.0925798           | 0.0907413           |
| InsertionSort              | 0.0498009               | 0.00002858          | 0.0998162           |
| QuickSort (Random Pivot)   | 0.00208098              | 0.00159398          | 0.00164398          |
| QuickSort (Median of Medians)| 0.00618445            | 0.00897851          | 0.00785229          |
| QuickSort (First Element as Pivot)| 0.00185528       | 0.00864063          | 0.424509            |

### Bubble Sort

- **Best Case**: Occurs when the input array is already sorted. In this case, the algorithm only requires a single pass to determine that no swaps are needed. This can be seen from the above figure for the sorted array case.
- **Worst Case**: Occurs when the input array is in reverse order. This results in the maximum number of comparisons and swaps in each pass. This can be seen from the above figure for the array sorted in descending order case.
- **Average Case**: Occurs when the input data is random or partially sorted, resulting in an average number of comparisons and swaps. This can be seen from the above figure for the unsorted array case.

### Selection Sort

- **Best Case**: There is no distinction in the number of comparisons, regardless of the input data. Selection sort always performs the same number of comparisons, leading to a time complexity of O(n^2). This can be seen from the above figure.
- **Worst Case**: There is no distinction in the number of comparisons, regardless of the input data. Selection sort always performs the same number of comparisons, leading to a time complexity of O(n^2). This can be seen from the above figure.
- **Average Case**: Same as the worst case since it always performs the same number of comparisons. Selection sort always performs the same number of comparisons, leading to a time complexity of O(n^2). This can be seen from the above figure.

### Insertion Sort

- **Best Case**: Occurs when the input array is already sorted, requiring minimal comparisons and no swaps. This can be seen from the above figure for the sorted array case.
- **Worst Case**: Occurs when the input array is in reverse order, resulting in the maximum number of comparisons and swaps in each pass. This can be seen from the above figure for the array sorted in descending order case.
- **Average Case**: Occurs when the input data is random or partially sorted, leading to an average number of comparisons and swaps. This can be seen from the above figure for the unsorted array case.

### Quick Sort

- **Best Case**: Occurs when the pivot choices consistently divide the input into nearly equal partitions, resulting in O(n log n) time complexity. This can be seen for both quicksort with median of medians and quicksort with random pivot although quicksort with random pivot is almost always slightly better.
- **Worst Case**: Occurs when the pivot choices result in highly unbalanced partitions, such as always picking the smallest or largest element as the pivot. This leads to a time complexity of O(n^2). Can be seen in QuickSort (First Element as Pivot) for elements sorted in descending order case.
- **Average Case**: Occurs when the pivot choices are relatively balanced, leading to an average time complexity of O(n log n). This can be seen for both quicksort with median of medians and quicksort with random pivot although quicksort with random pivot is almost always slightly better.

### Merge Sort

- **Best Case**: The best-case scenario for Merge Sort is when the input array is already sorted. In this case, Merge Sort still divides the array into sub-arrays and merges them, but the merging step is more efficient because it involves fewer comparisons. Therefore, the best-case time complexity is O(n log n), which is the same as the average and worst-case time complexity.
- **Worst Case**:  The worst-case time complexity of Merge Sort is also O(n log n). The worst-case scenario occurs when the input array is in reverse order. In this case, Merge Sort still divides the array into sub-arrays and merges them, but it involves the maximum number of comparisons and operations.
- **Average Case**: The average-case time complexity of Merge Sort is O(n log n). This is because, on average, the algorithm divides the array into roughly log(n) levels of sub-arrays, and at each level, it performs n operations to merge the sub-arrays.
**In practice the time difference due to comparisons becomes insignificant as can be seen from the above graph

<!-- In practical applications, the best, worst, and average cases for sorting algorithms depend on various factors, such as the specific implementation and the characteristics of the input data. -->

## Sorting Algorithms Comparison with unsorted arrays of multiple sizes.

![Sorting Algorithms Comparison with multiple array sizes](Out-sizes.jpg)

| Array Size | BubbleSort | InsertionSort | MergeSort | QuickSort-FirstElementAsPivot | QuickSort-MedianOfMedians | QuickSort-RandomPivot | SelectionSort |
|------------|------------|---------------|-----------|-----------------------------|--------------------------|-----------------------|--------------|
| 1000       | 0.00365648 | 0.000555661   | 0.00014714 | 0.00014196                    | 0.000484261               | 0.00016538            | 0.00103854    |
| 2000       | 0.0146845  | 0.00210354    | 0.00023872 | 0.00029538                    | 0.00114896                | 0.0003632             | 0.00398476    |
| 3000       | 0.0312643  | 0.00456271    | 0.00034606 | 0.00046064                    | 0.00166602                | 0.000521401            | 0.00863605    |
| 4000       | 0.0569199  | 0.00794495    | 0.000473841 | 0.000660821                   | 0.00226228                | 0.000733501            | 0.0150887     |
| 5000       | 0.0929254  | 0.0128994    | 0.000612901 | 0.000913441                   | 0.00291344                | 0.000996901            | 0.0236315     |
| 6000       | 0.135279   | 0.0178972    | 0.000747521 | 0.0011237                    | 0.00356168                | 0.0011492              | 0.0338499     |
| 7000       | 0.180714   | 0.0240044    | 0.000915181 | 0.00211616                   | 0.00423959                | 0.00144734             | 0.0459197     |
| 8000       | 0.23951    | 0.0315626    | 0.00102388 | 0.00140992                   | 0.00482687                | 0.00158842             | 0.0608777     |
| 9000       | 0.308304   | 0.0403196    | 0.00115664 | 0.00167872                   | 0.00566543                | 0.00179116             | 0.0752637     |
| 10000      | 0.37936    | 0.050862     | 0.00132892 | 0.00189074                   | 0.00645383                | 0.00223842             | 0.093946      |


### Bubble, Selection, and Insertion Sort
   - Bubble, Selection, and Insertion Sort algorithms have a much steeper increase in execution time as the array size grows. This behavior is expected as these algorithms have a time complexity of O(n^2), where the execution time increases quadratically with the array size.
   - For each of these algorithms, the execution time increases significantly as the array size goes from 1000 to 10000, indicating their poor scalability with larger datasets.

### MergeSort and QuickSort
   - MergeSort and various QuickSort variants (Random Pivot, First Element as Pivot) exhibit significantly better performance as the array size increases compared to Bubble, Selection, and Insertion Sort.
   - These algorithms have an average-case time complexity of O(n log n), which makes them more efficient for larger dataset sizes.

### QuickSort Variants
   - The data shows that the QuickSort variants, including Random Pivot and First Element as Pivot, perform quite similarly and are consistently faster than Bubble, Selection, and Insertion Sort. This demonstrates the effectiveness of the QuickSort algorithm for sorting arrays in practice.

### Median of Medians QuickSort
   - The Median of Medians QuickSort variant performs slightly worse than the other QuickSort variants. This could be due to the additional overhead of selecting the median of medians as the pivot, which might not always provide significant benefits in practice, especially for small to moderately sized datasets.

### MergeSort vs. QuickSort
   - Both MergeSort and QuickSort variants show similar performance across the dataset sizes. This indicates that their average-case time complexities are indeed quite close, despite QuickSort being considered a bit more efficient in practice for many cases. The differences in execution time could be attributed to various factors, such as pivot selection and partitioning strategies.

In summary, the provided data clearly demonstrates the importance of algorithm choice in sorting tasks. Bubble, Selection, and Insertion Sort algorithms exhibit poor scalability with larger datasets due to their O(n^2) time complexity, while MergeSort and QuickSort variants with an average-case O(n log n) time complexity provide much better performance. Additionally, the data suggests that the Median of Medians QuickSort variant may not always offer a significant advantage over other QuickSort strategies in practical scenarios.

