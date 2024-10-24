import numpy as np
import matplotlib.pyplot as plt
import sys

# Function to find the minimum cost of multiplying the given chain of matrices
def matrix_chain_multiplication(dims):
    n = len(dims)
    # Create a table to store the minimum number of scalar multiplications
    m = np.zeros((n, n))

    # Initialize the diagonal elements of the table to 0
    for i in range(1, n):
        m[i][i] = 0

    # Fill the table in a bottom-up manner
    for chain_len in range(2, n):
        for i in range(1, n - chain_len + 1):
            j = i + chain_len - 1
            m[i][j] = sys.maxsize  # Initialize to maximum value

            # Try placing parentheses at different places to split the chain
            for k in range(i, j):
                cost = m[i][k] + m[k + 1][j] + dims[i - 1] * dims[k] * dims[j]
                if cost < m[i][j]:
                    m[i][j] = cost

    # Return the minimum cost for multiplying matrices from 1 to n-1
    return m[1][n - 1]

# Function to visualize the minimum multiplication costs based on different inputs
def visualize_matrix_chain_multiplication(dims_list):
    costs = []
    input_labels = []

    for dims in dims_list:
        cost = matrix_chain_multiplication(dims)
        costs.append(cost)
        input_labels.append(f"Chain {len(dims)-1}")

    # Plotting the results
    plt.figure(figsize=(8, 6))
    plt.plot(input_labels, costs, marker='o',color='green')
    plt.title('Minimum Multiplications for Different Matrix Chains')
    plt.xlabel('Input Size (Number of Matrices in Chain)')
    plt.ylabel('Minimum Multiplications')
    plt.grid(True)
    plt.show()

# Main function to get user input and call the matrix chain multiplication
def main():
    # Example matrix dimensions for 5 chains
    dims_list = [
        [10, 20, 30, 40, 30],  # 4 matrices: A1(10x20), A2(20x30), A3(30x40), A4(40x30)
        [5, 10, 20, 25],       # 3 matrices: A1(5x10), A2(10x20), A3(20x25)
        [30, 35, 15, 5, 10, 20, 25],  # 6 matrices: A1(30x35), ..., A6(20x25)
        [5, 10, 3, 12, 5, 50, 6],     # 6 matrices: A1(5x10), ..., A6(50x6)
        [20, 30, 15, 25, 10]    # 4 matrices: A1(20x30), A2(30x15), A3(15x25), A4(25x10)
    ]

    visualize_matrix_chain_multiplication(dims_list)

if __name__ == "__main__":
    main()