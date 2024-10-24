import time
import random
import matplotlib.pyplot as plt

# Structure to represent an item with weight and value
class Item:
    def __init__(self, weight, value):
        self.weight = weight
        self.value = value

# Function to sort items by value/weight ratio for the greedy approach
def sort_items_by_ratio(items):
    items.sort(key=lambda x: x.value / x.weight, reverse=True)

# Greedy approach to solve the 0/1 Knapsack problem
def greedy_knapsack(items, W):
    sort_items_by_ratio(items)  # Sort items by value/weight ratio

    total_value = 0  # Total value accumulated
    total_weight = 0  # Total weight accumulated

    for item in items:
        if total_weight + item.weight <= W:
            total_weight += item.weight  # Add item's weight to knapsack
            total_value += item.value  # Add item's value to total value

    return total_value  # Return the total value obtained by greedy method

# Dynamic Programming approach to solve the 0/1 Knapsack problem
def dynamic_knapsack(items, W):
    n = len(items)
    dp = [[0 for _ in range(W + 1)] for _ in range(n + 1)]  # Table to store optimal values for subproblems

    # Initialize the table
    for i in range(n + 1):
        for w in range(W + 1):
            if i == 0 or w == 0:
                dp[i][w] = 0
            elif items[i - 1].weight <= w:
                dp[i][w] = max(items[i - 1].value + dp[i - 1][w - items[i - 1].weight], dp[i - 1][w])
            else:
                dp[i][w] = dp[i - 1][w]

    return dp[n][W]  # Return the maximum value that can be obtained

# Function to generate random input sets
def generate_random_items(n):
    return [Item(random.randint(1, 10), random.randint(10, 100)) for _ in range(n)]

# Function to compare performance for different set sizes
def compare_algorithms():
    set_sizes = [5, 10, 15, 20, 25]  # Different set sizes to compare
    greedy_times = []
    dp_times = []
    W = 15  # Fixed capacity for knapsack

    for n in set_sizes:
        items = generate_random_items(n)

        # Measure the time for the greedy approach
        start_time = time.time()
        greedy_knapsack(items, W)
        greedy_time = time.time() - start_time
        greedy_times.append(greedy_time)

        # Measure the time for the dynamic programming approach
        start_time = time.time()
        dynamic_knapsack(items, W)
        dp_time = time.time() - start_time
        dp_times.append(dp_time)

    # Plotting results
    plt.plot(set_sizes, greedy_times, label='Greedy Approach', marker='o',color='orange')
    plt.plot(set_sizes, dp_times, label='Dynamic Programming', marker='o',color='green')

    plt.xlabel('Set Size')
    plt.ylabel('Execution Time (seconds)')
    plt.title('Performance of 0/1 Knapsack Algorithm')
    plt.legend()
    plt.grid()
    plt.show()

# Run the comparison
compare_algorithms()
