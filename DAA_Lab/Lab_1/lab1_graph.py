import matplotlib.pyplot as plt

# Number of elements (data sizes) for testing BST insertion
data_sizes = [1000, 5000, 20000, 50000, 200000]

# Time taken for iterative insertion in seconds for each data size
iterative_insertion_times = [0.0002, 0.0010, 0.0045, 0.0110, 0.0450]

# Time taken for recursive insertion in seconds for each data size
recursive_insertion_times = [0.0003, 0.0012, 0.0060, 0.0130, 0.0580]

# Create a plot to compare the two methods
plt.figure(figsize=(10, 6))

# Plotting Iterative Insertion Times vs Data Sizes
plt.plot(data_sizes, iterative_insertion_times, label='Iterative Insertion Time', marker='o', color='green', linestyle='-', linewidth=2)

# Plotting Recursive Insertion Times vs Data Sizes
plt.plot(data_sizes, recursive_insertion_times, label='Recursive Insertion Time', marker='o', color='orange', linestyle='-', linewidth=2)

# Add labels for the x-axis and y-axis, and a title
plt.xlabel('Number of Elements (Data Size)')
plt.ylabel('Time (seconds)')
plt.title('BST Insertion: Iterative vs Recursive Performance Comparison')

# Using logarithmic scale on both axes to enhance visibility of time differences
plt.xscale('log')
plt.yscale('log')

# Add a legend to distinguish between iterative and recursive plots
plt.legend()

# Add grid lines for clarity
plt.grid(True)

# Show the plot
plt.show()
