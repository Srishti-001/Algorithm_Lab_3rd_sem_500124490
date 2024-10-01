//3) Compare the performance of Strassen method of matrix multiplication with traditional way of matrix multiplication.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to dynamically allocate memory for a square matrix of size n
int** createSquareMatrix(int size) {
    int** matrix = (int**)malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++) {
        matrix[i] = (int*)malloc(size * sizeof(int));
    }
    return matrix;
}

// Function to deallocate memory of a square matrix
void releaseMatrix(int** matrix, int size) {
    for (int i = 0; i < size; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

// Function to perform element-wise addition of two matrices
void addMatrices(int** firstMatrix, int** secondMatrix, int** resultMatrix, int size) {
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            resultMatrix[row][col] = firstMatrix[row][col] + secondMatrix[row][col];
        }
    }
}

// Function to perform element-wise subtraction of two matrices
void subtractMatrices(int** firstMatrix, int** secondMatrix, int** resultMatrix, int size) {
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            resultMatrix[row][col] = firstMatrix[row][col] - secondMatrix[row][col];
        }
    }
}

// Standard matrix multiplication implementation
void classicMatrixMultiplication(int** firstMatrix, int** secondMatrix, int** resultMatrix, int size) {
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            resultMatrix[row][col] = 0;  // Initialize result cell to zero
            for (int k = 0; k < size; k++) {
                resultMatrix[row][col] += firstMatrix[row][k] * secondMatrix[k][col];
            }
        }
    }
}

// Strassen's algorithm for matrix multiplication
void strassenMatrixMultiplication(int** firstMatrix, int** secondMatrix, int** resultMatrix, int size) {
    if (size <= 64) {  // Use classical multiplication for smaller matrices
        classicMatrixMultiplication(firstMatrix, secondMatrix, resultMatrix, size);
        return;
    }

    int halfSize = size / 2;

    // Allocate memory for submatrices
    int** A11 = createSquareMatrix(halfSize);
    int** A12 = createSquareMatrix(halfSize);
    int** A21 = createSquareMatrix(halfSize);
    int** A22 = createSquareMatrix(halfSize);
    int** B11 = createSquareMatrix(halfSize);
    int** B12 = createSquareMatrix(halfSize);
    int** B21 = createSquareMatrix(halfSize);
    int** B22 = createSquareMatrix(halfSize);

    // Allocate matrices for products P1 to P7
    int** P1 = createSquareMatrix(halfSize);
    int** P2 = createSquareMatrix(halfSize);
    int** P3 = createSquareMatrix(halfSize);
    int** P4 = createSquareMatrix(halfSize);
    int** P5 = createSquareMatrix(halfSize);
    int** P6 = createSquareMatrix(halfSize);
    int** P7 = createSquareMatrix(halfSize);

    // Allocate space for sub-results C11, C12, C21, C22
    int** C11 = createSquareMatrix(halfSize);
    int** C12 = createSquareMatrix(halfSize);
    int** C21 = createSquareMatrix(halfSize);
    int** C22 = createSquareMatrix(halfSize);

    // Temporary matrices for intermediate calculations
    int** tempA = createSquareMatrix(halfSize);
    int** tempB = createSquareMatrix(halfSize);

    // Splitting matrices into four submatrices
    for (int row = 0; row < halfSize; row++) {
        for (int col = 0; col < halfSize; col++) {
            A11[row][col] = firstMatrix[row][col];
            A12[row][col] = firstMatrix[row][col + halfSize];
            A21[row][col] = firstMatrix[row + halfSize][col];
            A22[row][col] = firstMatrix[row + halfSize][col + halfSize];

            B11[row][col] = secondMatrix[row][col];
            B12[row][col] = secondMatrix[row][col + halfSize];
            B21[row][col] = secondMatrix[row + halfSize][col];
            B22[row][col] = secondMatrix[row + halfSize][col + halfSize];
        }
    }

    // Calculate P1 to P7 using Strassen's formulas
    addMatrices(A11, A22, tempA, halfSize);
    addMatrices(B11, B22, tempB, halfSize);
    strassenMatrixMultiplication(tempA, tempB, P1, halfSize);  // P1 = (A11 + A22) * (B11 + B22)

    addMatrices(A21, A22, tempA, halfSize);
    strassenMatrixMultiplication(tempA, B11, P2, halfSize);  // P2 = (A21 + A22) * B11

    subtractMatrices(B12, B22, tempB, halfSize);
    strassenMatrixMultiplication(A11, tempB, P3, halfSize);  // P3 = A11 * (B12 - B22)

    subtractMatrices(B21, B11, tempB, halfSize);
    strassenMatrixMultiplication(A22, tempB, P4, halfSize);  // P4 = A22 * (B21 - B11)

    addMatrices(A11, A12, tempA, halfSize);
    strassenMatrixMultiplication(tempA, B22, P5, halfSize);  // P5 = (A11 + A12) * B22

    subtractMatrices(A21, A11, tempA, halfSize);
    addMatrices(B11, B12, tempB, halfSize);
    strassenMatrixMultiplication(tempA, tempB, P6, halfSize);  // P6 = (A21 - A11) * (B11 + B12)

    subtractMatrices(A12, A22, tempA, halfSize);
    addMatrices(B21, B22, tempB, halfSize);
    strassenMatrixMultiplication(tempA, tempB, P7, halfSize);  // P7 = (A12 - A22) * (B21 + B22)

    // Calculate C11, C12, C21, C22 from P1 to P7
    addMatrices(P1, P4, tempA, halfSize);
    subtractMatrices(tempA, P5, tempB, halfSize);
    addMatrices(tempB, P7, C11, halfSize);  // C11 = P1 + P4 - P5 + P7

    addMatrices(P3, P5, C12, halfSize);  // C12 = P3 + P5

    addMatrices(P2, P4, C21, halfSize);  // C21 = P2 + P4

    addMatrices(P1, P3, tempA, halfSize);
    subtractMatrices(tempA, P2, tempB, halfSize);
    addMatrices(tempB, P6, C22, halfSize);  // C22 = P1 + P3 - P2 + P6

    // Combining submatrices into the final result matrix
    for (int row = 0; row < halfSize; row++) {
        for (int col = 0; col < halfSize; col++) {
            resultMatrix[row][col] = C11[row][col];
            resultMatrix[row][col + halfSize] = C12[row][col];
            resultMatrix[row + halfSize][col] = C21[row][col];
            resultMatrix[row + halfSize][col + halfSize] = C22[row][col];
        }
    }

    // Deallocate memory for all submatrices
    releaseMatrix(A11, halfSize); releaseMatrix(A12, halfSize);
    releaseMatrix(A21, halfSize); releaseMatrix(A22, halfSize);
    releaseMatrix(B11, halfSize); releaseMatrix(B12, halfSize);
    releaseMatrix(B21, halfSize); releaseMatrix(B22, halfSize);
    releaseMatrix(P1, halfSize); releaseMatrix(P2, halfSize);
    releaseMatrix(P3, halfSize); releaseMatrix(P4, halfSize);
    releaseMatrix(P5, halfSize); releaseMatrix(P6, halfSize);
    releaseMatrix(P7, halfSize);
    releaseMatrix(C11, halfSize); releaseMatrix(C12, halfSize);
    releaseMatrix(C21, halfSize); releaseMatrix(C22, halfSize);
    releaseMatrix(tempA, halfSize); releaseMatrix(tempB, halfSize);
}

// Function to measure execution time of matrix multiplication
double timeExecution(void (*multiplyFunc)(int**, int**, int**, int), int** firstMatrix, int** secondMatrix, int** resultMatrix, int size) {
    clock_t start, end;
    double duration;

    start = clock();
    multiplyFunc(firstMatrix, secondMatrix, resultMatrix, size);
    end = clock();

    duration = ((double)(end - start)) / CLOCKS_PER_SEC; // Convert clock ticks to seconds
    return duration;
}

int main() {
    srand(time(NULL));  // Seed random number generator for reproducibility

    // Define matrix sizes to test
    int matrixSizes[] = {64, 128, 256, 512, 1024, 2048};
    int numSizes = sizeof(matrixSizes) / sizeof(matrixSizes[0]);

    // Print header for results table
    printf("Matrix Size\tClassic Time\tStrassen Time\n");

    // Loop through defined matrix sizes
    for (int index = 0; index < numSizes; index++) {
        int size = matrixSizes[index];

        // Allocate matrices A, B, and C
        int** matrixA = createSquareMatrix(size);
        int** matrixB = createSquareMatrix(size);
        int** matrixC = createSquareMatrix(size);

        // Initialize matrices A and B with random integers from 0 to 9
        for (int row = 0; row < size; row++) {
            for (int col = 0; col < size; col++) {
                matrixA[row][col] = rand() % 10; // Random value for matrix A
                matrixB[row][col] = rand() % 10; // Random value for matrix B
            }
        }

        // Measure and print execution times for both multiplication methods
        double classicTime = timeExecution(classicMatrixMultiplication, matrixA, matrixB, matrixC, size);
        double strassenTime = timeExecution(strassenMatrixMultiplication, matrixA, matrixB, matrixC, size);

        printf("%d x %d\t%.6f\t\t%.6f\n", size, size, classicTime, strassenTime);

        // Deallocate memory for matrices
        releaseMatrix(matrixA, size);
        releaseMatrix(matrixB, size);
        releaseMatrix(matrixC, size);
    }

    return 0;
}