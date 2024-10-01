//2) Implement divide and conquer based merge sort and quick sort algorithms and compare their performance for the same set of elements. 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Function to merge two subarrays for Merge Sort
void mergeSortedSubarrays(int array[], int left, int mid, int right) {
    int i, j, k;
    int sizeLeft = mid - left + 1;
    int sizeRight = right - mid;

    // Temporary arrays to hold the two halves
    int leftArray[sizeLeft], rightArray[sizeRight];

    // Copy data to temporary arrays leftArray[] and rightArray[]
    for (i = 0; i < sizeLeft; i++)
        leftArray[i] = array[left + i];
    for (j = 0; j < sizeRight; j++)
        rightArray[j] = array[mid + 1 + j];

    // Initial indexes for merging
    i = 0; 
    j = 0; 
    k = left;

    // Merge the arrays back into the original array
    while (i < sizeLeft && j < sizeRight) {
        if (leftArray[i] <= rightArray[j]) {
            array[k] = leftArray[i];
            i++;
        } else {
            array[k] = rightArray[j];
            j++;
        }
        k++;
    }

    // Copy remaining elements of leftArray[], if any
    while (i < sizeLeft) {
        array[k] = leftArray[i];
        i++;
        k++;
    }

    // Copy remaining elements of rightArray[], if any
    while (j < sizeRight) {
        array[k] = rightArray[j];
        j++;
        k++;
    }
}

// Merge Sort function using divide and conquer
void mergeSortAlgorithm(int array[], int left, int right) {
    if (left < right) {
        // Find the middle point to divide the array into two halves
        int mid = left + (right - left) / 2;

        // Recursively sort both halves
        mergeSortAlgorithm(array, left, mid);
        mergeSortAlgorithm(array, mid + 1, right);

        // Merge the sorted halves
        mergeSortedSubarrays(array, left, mid, right);
    }
}

// Function to swap two elements for Quick Sort
void swapElements(int* first, int* second) {
    int temp = *first;
    *first = *second;
    *second = temp;
}

// Partition function for Quick Sort
int partitionArray(int array[], int low, int high) {
    int pivot = array[high]; // Pivot element
    int i = (low - 1); // Index of smaller element

    for (int j = low; j <= high - 1; j++) {
        if (array[j] < pivot) {
            i++;
            swapElements(&array[i], &array[j]);
        }
    }
    swapElements(&array[i + 1], &array[high]);
    return (i + 1);
}

// Quick Sort function using divide and conquer
void quickSortAlgorithm(int array[], int low, int high) {
    if (low < high) {
        // Partition the array around the pivot element
        int partitionIndex = partitionArray(array, low, high);

        // Recursively sort the subarrays before and after partition
        quickSortAlgorithm(array, low, partitionIndex - 1);
        quickSortAlgorithm(array, partitionIndex + 1, high);
    }
}

// Function to generate an array with random elements
void fillArrayWithRandomData(int array[], int size) {
    for (int i = 0; i < size; i++) {
        array[i] = rand() % 10000;  // Random values between 0 and 9999
    }
}

// Function to measure the execution time of sorting algorithms
double calculateSortingTime(void (*sortingAlgorithm)(int[], int, int), int array[], int size) {
    clock_t start, end;
    double timeElapsed;

    // Create a copy of the array to sort
    int* arrayCopy = (int*)malloc(size * sizeof(int));
    memcpy(arrayCopy, array, size * sizeof(int));

    // Measure the time taken to sort the array
    start = clock();
    sortingAlgorithm(arrayCopy, 0, size - 1);
    end = clock();

    timeElapsed = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Free the array copy
    free(arrayCopy);
    return timeElapsed;
}

int main() {
    // Seed random number generator
    srand(time(NULL));

    // Array sizes to test
    int arraySizes[] = {2000, 10000, 20000, 80000, 150000};
    int numberOfTests = sizeof(arraySizes) / sizeof(arraySizes[0]);

    // Displaying the results
    printf("Test No.\tArray Size\tMerge Sort Time\t\tQuick Sort Time\n");

    // Run tests for each array size
    for (int testIndex = 0; testIndex < numberOfTests; testIndex++) {
        int size = arraySizes[testIndex];
        int* array = (int*)malloc(size * sizeof(int));

        // Fill the array with random values
        fillArrayWithRandomData(array, size);

        // Measure time for merge sort
        double mergeSortDuration = calculateSortingTime(mergeSortAlgorithm, array, size);

        // Measure time for quick sort
        double quickSortDuration = calculateSortingTime(quickSortAlgorithm, array, size);

        // Print results
        printf("%d\t\t%d\t\t%.6f\t\t%.6f\n", testIndex + 1, size, mergeSortDuration, quickSortDuration);

        // Free the array memory
        free(array);
    }

    return 0;
}