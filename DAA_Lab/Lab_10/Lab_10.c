//10) Compare the performance of Rabin-Karp, Knuth-Morris-Pratt and naive string matching algorithms.

#include <stdio.h>
#include <string.h>
#include <math.h>

#define d 256 // Number of characters in the input alphabet for Rabin-Karp
#define q 101 // A prime number for Rabin-Karp hash function

// Naive String Matching

void naiveStringMatching(char *text, char *pattern) {
    int n = strlen(text);
    int m = strlen(pattern);

    printf("Naive String Matching:\n");
    for (int i = 0; i <= n - m; i++) {
        int j;
        for (j = 0; j < m; j++) {
            if (text[i + j] != pattern[j]) {
                break;
            }
        }
        if (j == m) {
            printf("Pattern found at index %d\n", i);
        }
    }
}

// Rabin-Karp Algorithm

// Rabin-Karp function to search pattern in the text
void rabinKarp(char *text, char *pattern) {
    int n = strlen(text);
    int m = strlen(pattern);
    int p = 0; // Hash value for pattern
    int t = 0; // Hash value for text
    int h = 1;

    // Compute the value of h = pow(d, m-1) % q
    for (int i = 0; i < m - 1; i++) {
        h = (h * d) % q;
    }

    // Calculate initial hash values for the pattern and first window of the text
    for (int i = 0; i < m; i++) {
        p = (d * p + pattern[i]) % q;
        t = (d * t + text[i]) % q;
    }

    printf("\nRabin-Karp Algorithm:\n");
    // Slide the pattern over the text
    for (int i = 0; i <= n - m; i++) {
        // Check if hash values match
        if (p == t) {
            // If the hash values match, check characters one by one
            int j;
            for (j = 0; j < m; j++) {
                if (text[i + j] != pattern[j]) {
                    break;
                }
            }
            if (j == m) {
                printf("Pattern found at index %d\n", i);
            }
        }

        // Calculate hash value for the next window of the text
        if (i < n - m) {
            t = (d * (t - text[i] * h) + text[i + m]) % q;
            if (t < 0) {
                t = t + q;
            }
        }
    }
}

//Knuth-Morris-Pratt Algorithm (KMP)

// Preprocess pattern to create the longest prefix suffix (LPS) array
void computeLPSArray(char *pattern, int m, int *lps) {
    int length = 0; // Length of the previous longest prefix suffix
    lps[0] = 0;     // LPS of first character is always 0
    int i = 1;

    while (i < m) {
        if (pattern[i] == pattern[length]) {
            length++;
            lps[i] = length;
            i++;
        } else {
            if (length != 0) {
                length = lps[length - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

// KMP algorithm to search pattern in the text
void KMP(char *text, char *pattern) {
    int n = strlen(text);
    int m = strlen(pattern);

    int lps[m]; // Array to hold longest prefix suffix values
    computeLPSArray(pattern, m, lps);

    int i = 0; // Index for text
    int j = 0; // Index for pattern

    printf("\nKnuth-Morris-Pratt (KMP) Algorithm:\n");
    while (i < n) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }

        if (j == m) {
            printf("Pattern found at index %d\n", i - j);
            j = lps[j - 1];
        } else if (i < n && pattern[j] != text[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }
}

//Main Function

int main() {
    char text[] = "ABABDABACDABABCABAB";
    char pattern[] = "ABABCABAB";

    // Naive String Matching
    naiveStringMatching(text, pattern);

    // Rabin-Karp Algorithm
    rabinKarp(text, pattern);

    // Knuth-Morris-Pratt (KMP) Algorithm
    KMP(text, pattern);

    return 0;
}