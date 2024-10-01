import matplotlib.pyplot as plt

# Data for Matrix Size, Traditional Time, and Strassen Time
matrix_size = ['64x64', '128x128', '256x256', '512x512', '1024x1024', '2048x2048']
traditional_time = [0.000000, 0.013000, 0.106000, 0.822000, 7.965000, 93.234000]
strassen_time = [0.000000, 0.013000, 0.086000, 0.610000, 4.240000, 29.705000]

# Create the plot
plt.figure(figsize=(10, 6))

# Plot the Traditional Time vs Matrix Size
plt.plot(matrix_size, traditional_time, label='Traditional Time', marker='o', color='green', linestyle='-', linewidth=2)

# Plot the Strassen Time vs Matrix Size
plt.plot(matrix_size, strassen_time, label='Strassen Time', marker='o', color='orange', linestyle='-', linewidth=2)

# Add labels and title
plt.xlabel('Matrix Size')
plt.ylabel('Time (seconds)')
plt.title('Performance Comparison: Traditional vs Strassen Matrix Multiplication')

# Add a legend
plt.legend()

# Add grid for better readability
plt.grid(True)

# Display the plot
plt.show()
