#include <stdio.h>

void bubble_sort(int len, int* arr);
void print_arr(int len, int* arr);

int main(void) {
    int arr[] = {4, 8, 1, 2, 3, 5, 7, 6, 0, 9};
    
    bubble_sort(10, arr);

    print_arr(10, arr);

    return 0;
}

void bubble_sort(int len, int* arr) {
    // each number will bubble it's way to it's correct position
    for (int i = 0; i < len - 1; i++) {
        // every iteration the "largest" bubbles it's way to the end
        
        int swap_count = 0; // to test if swap has happened
        
        for (int j = 0; j < len - i - 1; j++) {
            if (arr[j] > arr[j+1]) {
                // swap
                int temp_store = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp_store;

                swap_count++; // swap has happened
            }
        }
        // check if no swaps happened
        if (swap_count == 0) break;
    }
}

void print_arr(int len, int* arr) {
    printf("[ ");
    for (int i = 0; i< len; i++)
        printf("%d, ", arr[i]);
    printf("\b\b ]\n");
}