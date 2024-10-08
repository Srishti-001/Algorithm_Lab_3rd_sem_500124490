import matplotlib.pyplot as plt

# Data for Array Sizes, Merge Sort Time, and Quick Sort Time based on previous C implementation
array_sizes = [2000, 10000, 20000, 80000, 150000]
merge_sort_durations = [0.001000, 0.002000, 0.004000, 0.020000, 0.035000]  # Example times for merge sort
quick_sort_durations = [0.000800, 0.001500, 0.003000, 0.015000, 0.030000]  # Example times for quick sort

# Create a new figure for the plot
plt.figure(figsize=(10, 6))

# Plot Merge Sort Time against Array Sizes
plt.plot(array_sizes, merge_sort_durations, label='Merge Sort Duration', marker='o', color='green', linestyle='-', linewidth=2)

# Plot Quick Sort Time against Array Sizes
plt.plot(array_sizes, quick_sort_durations, label='Quick Sort Duration', marker='o', color='orange', linestyle='-', linewidth=2)

# Add labels to the x-axis and y-axis
plt.xlabel('Array Size (Number of Elements)')
plt.ylabel('Execution Time (seconds)')

# Add a title to the plot
plt.title('Merge Sort vs Quick Sort: Time Complexity Analysis')

# Add a legend to differentiate between Merge Sort and Quick Sort
plt.legend()

# Add a grid for better readability of the plot
plt.grid(True)

# Display the plot
plt.show()
