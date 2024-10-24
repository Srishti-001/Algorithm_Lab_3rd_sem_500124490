//8) Implement the sum of subset.

#include <stdio.h>

// Function to print the current subset
void printSubset(int subset[], int subsetSize) {
    printf("{ ");
    for (int i = 0; i < subsetSize; i++) {
        printf("%d ", subset[i]);
    }
    printf("}\n");
}

// Recursive function to find subsets that sum up to the target
void sumOfSubsets(int set[], int subset[], int subsetSize, int total, int target, int index, int n) {
    // If the total is equal to the target, print the subset
    if (total == target) {
        printSubset(subset, subsetSize);
        return;
    }

    // If the total exceeds the target or no more items to include, return
    if (total > target || index == n) {
        return;
    }

    // Include the current element in the subset and recurse
    subset[subsetSize] = set[index];
    sumOfSubsets(set, subset, subsetSize + 1, total + set[index], target, index + 1, n);

    // Exclude the current element from the subset and recurse
    sumOfSubsets(set, subset, subsetSize, total, target, index + 1, n);
}

int main() {
    // Define the set of elements
    int set[] = {10, 7, 5, 18, 12, 20, 15};
    int n = sizeof(set) / sizeof(set[0]); // Number of elements in the set

    int target = 35; // Target sum to find subsets
    int subset[n]; // Array to store current subset during recursion

    // Call the sumOfSubsets function to find all subsets that sum to the target
    printf("Subsets whose sum is %d:\n", target);
    sumOfSubsets(set, subset, 0, 0, target, 0, n);

    return 0;
}