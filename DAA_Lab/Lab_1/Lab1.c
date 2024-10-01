#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Structure for a node in a Binary Search Tree (BST)
struct TreeNode {
    int key;
    struct TreeNode* left;
    struct TreeNode* right;
};

// Create a new TreeNode
struct TreeNode* createTreeNode(int key) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->key = key;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Iterative insertion into the BST
struct TreeNode* insertIterative(struct TreeNode* root, int key) {
    struct TreeNode* newNode = createTreeNode(key);
    if (root == NULL) return newNode;

    struct TreeNode* parent = NULL;
    struct TreeNode* current = root;
    
    while (current != NULL) {
        parent = current;
        if (key < current->key)
            current = current->left;
        else if (key > current->key)
            current = current->right;
        else
            return root; // No duplicates allowed
    }

    if (key < parent->key)
        parent->left = newNode;
    else
        parent->right = newNode;

    return root;
}

// Recursive insertion into the BST
struct TreeNode* insertRecursive(struct TreeNode* root, int key) {
    if (root == NULL) return createTreeNode(key);

    if (key < root->key)
        root->left = insertRecursive(root->left, key);
    else if (key > root->key)
        root->right = insertRecursive(root->right, key);

    return root;
}

// In-order traversal to print the BST (for validation)
void inOrderTraversal(struct TreeNode* root) {
    if (root != NULL) {
        inOrderTraversal(root->left);
        printf("%d ", root->key);
        inOrderTraversal(root->right);
    }
}

// Function to compare the execution time of iterative and recursive insertions
void compareInsertPerformance(int dataSets[5][10], int setSizes[5]) {
    for (int i = 0; i < 5; i++) {
        printf("\n--- Data Set %d ---\n", i + 1);
        struct TreeNode* iterativeRoot = NULL;  // For iterative insertion
        struct TreeNode* recursiveRoot = NULL;  // For recursive insertion

        // Measure time for iterative insertion
        clock_t startIterative = clock();
        for (int j = 0; j < setSizes[i]; j++) {
            iterativeRoot = insertIterative(iterativeRoot, dataSets[i][j]);
        }
        clock_t endIterative = clock();
        double iterativeTime = ((double)(endIterative - startIterative)) / CLOCKS_PER_SEC;

        // Measure time for recursive insertion
        clock_t startRecursive = clock();
        for (int j = 0; j < setSizes[i]; j++) {
            recursiveRoot = insertRecursive(recursiveRoot, dataSets[i][j]);
        }
        clock_t endRecursive = clock();
        double recursiveTime = ((double)(endRecursive - startRecursive)) / CLOCKS_PER_SEC;

        printf("Iterative Insertion Time: %f seconds\n", iterativeTime);
        printf("Recursive Insertion Time: %f seconds\n", recursiveTime);

        // Optional: Print the BSTs (for validation)
        printf("In-order Traversal (Iterative): ");
        inOrderTraversal(iterativeRoot);
        printf("\nIn-order Traversal (Recursive): ");
        inOrderTraversal(recursiveRoot);
        printf("\n");
    }
}

// Driver function
int main() {
    // Define five different data sets
    int dataSets[5][10] = {
        {45, 25, 65, 15, 35, 55, 75},  // 7 keys
        {5, 10, 15, 20, 25, 30, 35, 40, 45}, // 9 keys
        {50, 30, 70, 20, 40, 60, 80},  // 7 keys
        {90, 85, 80, 95, 100}, // 5 keys
        {12, 32, 24, 54, 76, 87, 34}  // 7 keys
    };

    // Define the size of each data set
    int setSizes[5] = {7, 9, 7, 5, 7};

    // Compare insertion performance for both methods
    compareInsertPerformance(dataSets, setSizes);

    return 0;
}