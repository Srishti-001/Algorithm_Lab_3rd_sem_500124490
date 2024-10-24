import time
import random
import matplotlib.pyplot as plt

# Function to print the current subset
def print_subset(subset):
    print(f"{subset}")

# Recursive function to find subsets that sum up to the target
def sum_of_subsets(set_, subset, total, target, index, n, result):
    # If the total is equal to the target, store the subset
    if total == target:
        result.append(subset.copy())
        return

    # If the total exceeds the target or no more items to include, return
    if total > target or index == n:
        return

    # Include the current element in the subset and recurse
    subset.append(set_[index])
    sum_of_subsets(set_, subset, total + set_[index], target, index + 1, n, result)

    # Exclude the current element from the subset and recurse
    subset.pop()
    sum_of_subsets(set_, subset, total, target, index + 1, n, result)

# Function to generate random input sets
def generate_random_set(n):
    return [random.randint(1, 20) for _ in range(n)]

# Function to compare performance for different set sizes
def compare_algorithms():
    target = 50  # Target sum
    set_sizes = [5, 10, 15, 20, 25]  # Different set sizes to compare
    execution_times = []

    for n in set_sizes:
        set_ = generate_random_set(n)
        subset = []
        result = []

        # Measure the time for sum_of_subsets
        start_time = time.time()
        sum_of_subsets(set_, subset, 0, target, 0, n, result)
        execution_time = time.time() - start_time
        execution_times.append(execution_time)

        print(f"Set Size: {n}, Subsets found: {len(result)}")

    # Plotting results
    plt.plot(set_sizes, execution_times, label='Sum of Subsets',color='orange')

    plt.xlabel('Set Size')
    plt.ylabel('Execution Time (seconds)')
    plt.title('Performance of Sum of Subsets Algorithm')
    plt.legend()
    plt.show()

# Run the comparison
compare_algorithms()
