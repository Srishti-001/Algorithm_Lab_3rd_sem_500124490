/*5) Get a detailed insight of dynamic programming approach by the implementation of 
Matrix Chain Multiplication problem and see the impact of parenthesis positioning 
on time requirements for matrix multiplication.
*/

#include <stdio.h>
#include <limits.h>

// Function to find the minimum cost of multiplying the given chain of matrices
int matrixChainMultiplication(int dims[], int n) {
    // Create a table to store the minimum number of scalar multiplications
    // m[i][j] will store the minimum cost for multiplying matrices from i to j
    int m[n][n];

    // Initialize the diagonal elements of the table to 0
    // because multiplying one matrix requires no multiplication
    for (int i = 1; i < n; i++) {
        m[i][i] = 0;
    }

    // Fill the table in a bottom-up manner
    for (int chainLen = 2; chainLen < n; chainLen++) {
        for (int i = 1; i < n - chainLen + 1; i++) {
            int j = i + chainLen - 1;
            m[i][j] = INT_MAX;  // Initialize to maximum value

            // Try placing parenthesis at different places to split the chain
            for (int k = i; k < j; k++) {
                // Cost of multiplying matrices from i to k and k+1 to j
                // plus cost of multiplying the resulting two matrices
                int cost = m[i][k] + m[k + 1][j] + dims[i - 1] * dims[k] * dims[j];

                // Update the minimum cost for multiplying matrices from i to j
                if (cost < m[i][j]) {
                    m[i][j] = cost;
                }
            }
        }
    }

    // Return the minimum cost for multiplying matrices from 1 to n-1
    return m[1][n - 1];
}

// Main function to test the matrix chain multiplication problem
int main() {
    // Array representing the dimensions of matrices
    int dims[] = {10, 20, 30, 40, 30};

    // n is the number of matrices (size of dims array minus 1)
    int n = sizeof(dims) / sizeof(dims[0]);

    // Call the matrix chain multiplication function and print the result
    printf("Minimum number of multiplications is %d\n", matrixChainMultiplication(dims, n));

    return 0;
}
