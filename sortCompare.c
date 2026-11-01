#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long long insertion_sort(int arr[], int n) {
    long long comparisons = 0;
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0) {
            comparisons++;
            if (arr[j] > key) {
                arr[j + 1] = arr[j];
                j--;
            }
            else {
                break;
            }
        }
        arr[j + 1] = key;
    }
    return comparisons;
}

long long shell_sort_original(int arr[], int n) {
    long long comparisons = 0;
    for (int h = n / 2; h > 0; h /= 2) {
        for (int i = h; i < n; i++) {
            int key = arr[i];
            int j = i - h;
            while (j >= 0) {
                comparisons++;
                if (arr[j] > key) {
                    arr[j + h] = arr[j];
                    j -= h;
                }
                else {
                    break;
                }
            }
            arr[j + h] = key;
        }
    }
    return comparisons;
}

long long shell_sort_knuth(int arr[], int n) {
    long long comparisons = 0;
    int gaps[30];
    int count = 0;
    int current = 1;

    while (current < n) {
        gaps[count++] = current;
        current = 3 * current + 1;
    }

    for (int idx = count - 1; idx >= 0; idx--) {
        int h_val = gaps[idx];
        for (int i = h_val; i < n; i++) {
            int key = arr[i];
            int j = i - h_val;
            while (j >= 0) {
                comparisons++;
                if (arr[j] > key) {
                    arr[j + h_val] = arr[j];
                    j -= h_val;
                }
                else {
                    break;
                }
            }
            arr[j + h_val] = key;
        }
    }
    return comparisons;
}

void copy_array(const int src[], int dest[], int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = src[i];
    }
}

int is_sorted(const int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) return 0;
    }
    return 1;
}

int main() {
    srand((unsigned int)time(NULL));
    int sizes[] = { 1000, 2000, 4000, 8000, 16000, 20000 };
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    for (int s = 0; s < num_sizes; s++) {
        int n = sizes[s];
        int* original = (int*)malloc(sizeof(int) * n);
        int* arr1 = (int*)malloc(sizeof(int) * n);
        int* arr2 = (int*)malloc(sizeof(int) * n);
        int* arr3 = (int*)malloc(sizeof(int) * n);

        for (int i = 0; i < n; i++) {
            original[i] = rand() % 1000000;
        }

        copy_array(original, arr1, n);
        long long comp1 = insertion_sort(arr1, n);
        if (!is_sorted(arr1, n)) {
            printf("Error: Insertion Sort failed for size %d\n", n);
        }

        copy_array(original, arr2, n);
        long long comp2 = shell_sort_original(arr2, n);
        if (!is_sorted(arr2, n)) {
            printf("Error: Shell Sort (Original) failed for size %d\n", n);
        }

        copy_array(original, arr3, n);
        long long comp3 = shell_sort_knuth(arr3, n);
        if (!is_sorted(arr3, n)) {
            printf("Error: Shell Sort (Knuth) failed for size %d\n", n);
        }

        printf("Data Size : %d\n\n", n);
        printf("Insertion Sort       : %lld comparisons\n", comp1);
        printf("Shell Sort (Original): %lld comparisons\n", comp2);
        printf("Shell Sort (Knuth)   : %lld comparisons\n\n", comp3);

        free(original);
        free(arr1);
        free(arr2);
        free(arr3);
    }

    return 0;
}