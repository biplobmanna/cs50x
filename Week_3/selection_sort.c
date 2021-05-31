#include <stdio.h>

void selection_sort(int len, int* arr);
void print_arr(int len, int* arr);

int main(void) {
    int arr[] = {4, 8, 1, 2, 3, 5, 7, 6, 0, 9};
    
    selection_sort(10, arr);

    print_arr(10, arr);

    return 0;
}

void selection_sort(int len, int* arr) {
    // find the lowest/highest num
    // repace with current indexed num
    for (int i = 0; i < len; i++) {
        // find lowest num
        int lowest_num = arr[i];
        int lowest_ix = i;
        for (int j = i + 1; j < len; j++) {
            if (arr[j] < lowest_num) {
                lowest_num = arr[j];
                lowest_ix = j;
            }
        }

        // swap
        arr[lowest_ix] = arr[i];
        arr[i] = lowest_num;
    }
}

void print_arr(int len, int* arr) {
    printf("[ ");
    for (int i = 0; i< len; i++)
        printf("%d, ", arr[i]);
    printf("\b\b ]\n");
}