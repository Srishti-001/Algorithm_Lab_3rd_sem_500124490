//7) Through 0/1 Knapsack problem, analyze the greedy and dynamic programming approach for the same dataset.

#include <stdio.h>

// Structure to represent an item with weight and value
struct Item {
    int weight;
    int value;
};

// Utility function to swap two items (used in sorting)
void swap(struct Item* a, struct Item* b) {
    struct Item temp = *a;
    *a = *b;
    *b = temp;
}

// Function to sort items by value/weight ratio for the greedy approach
void sortItemsByRatio(struct Item items[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            float ratio1 = (float)items[j].value / items[j].weight;
            float ratio2 = (float)items[j+1].value / items[j+1].weight;
            if (ratio1 < ratio2) {
                swap(&items[j], &items[j+1]);
            }
        }
    }
}

// Greedy approach to solve the 0/1 Knapsack problem
int greedyKnapsack(struct Item items[], int n, int W) {
    sortItemsByRatio(items, n); // Sort items by value/weight ratio

    int totalValue = 0; // Total value accumulated
    int totalWeight = 0; // Total weight accumulated

    for (int i = 0; i < n; i++) {
        if (totalWeight + items[i].weight <= W) {
            totalWeight += items[i].weight; // Add item's weight to knapsack
            totalValue += items[i].value;   // Add item's value to total value
        }
    }

    return totalValue; // Return the total value obtained by greedy method
}

// Dynamic Programming approach to solve the 0/1 Knapsack problem
int dynamicKnapsack(struct Item items[], int n, int W) {
    int dp[n+1][W+1]; // Table to store optimal values for subproblems

    // Initialize the table
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (i == 0 || w == 0)
                dp[i][w] = 0;
            else if (items[i-1].weight <= w)
                dp[i][w] = (items[i-1].value + dp[i-1][w - items[i-1].weight] > dp[i-1][w]) ?
                            items[i-1].value + dp[i-1][w - items[i-1].weight] : dp[i-1][w];
            else
                dp[i][w] = dp[i-1][w];
        }
    }

    return dp[n][W]; // Return the maximum value that can be obtained
}

int main() {
    // Define the set of items
    struct Item items[] = {
        {2, 40}, {3, 50}, {5, 100}, {7, 130}
    };
    
    int n = sizeof(items)/sizeof(items[0]); // Number of items
    int W = 10; // Capacity of the knapsack

    // Greedy approach result
    int greedyResult = greedyKnapsack(items, n, W);
    printf("Greedy Approach: Maximum Value = %d\n", greedyResult);

    // Dynamic Programming approach result
    int dpResult = dynamicKnapsack(items, n, W);
    printf("Dynamic Programming Approach: Maximum Value = %d\n", dpResult);

    return 0;
}