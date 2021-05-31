#include <stdio.h>
#include <stdlib.h>

void print_arr(int len, int* arr);
int merge_sort(int* arr, int start_ix, int end_ix);
void merge(int* arr, int start_ix, int mid_ix, int end_ix);

int main(void) {
    int arr[] = {4, 8, 1, 2, 3, 5, 7, 6, 0, 9};
    
    merge_sort(arr, 0, 9);

    print_arr(10, arr);

    return 0;
}

void print_arr(int len, int* arr) {
    printf("[ ");
    for (int i = 0; i< len; i++)
        printf("%d, ", arr[i]);
    printf("\b\b ]\n");
}

// ----------------------------------------------------------

int merge_sort(int* arr, int start_ix, int end_ix) {
    // divide until only one element remains
    if (end_ix - start_ix <= 0)
        return -1;
    
    int mid_ix = (start_ix + end_ix) / 2;
    // sort left-half
    merge_sort(arr, start_ix, mid_ix);
    // sort right-half
    merge_sort(arr, mid_ix + 1, end_ix);

    // merge both the halves
    merge(arr, start_ix, mid_ix, end_ix);
    return 0;
}


void merge(int* arr, int start_ix, int mid_ix, int end_ix) {
    // temporary array to store the sorted & merged array
    int *temp_arr = malloc((end_ix - start_ix + 1) * sizeof(int));
    int temp_ix = 0;

    // merge both the arrays
    int lix = start_ix, rix = mid_ix + 1;
    while (lix <= mid_ix && rix <= end_ix) {
        if (arr[lix] <= arr[rix])
            temp_arr[temp_ix++] = arr[lix++];
        else
            temp_arr[temp_ix++] = arr[rix++];
    }
    // merge whatever is remining in both the arrays
    for(;lix <= mid_ix; lix++)
        temp_arr[temp_ix++] = arr[lix];
    for(;rix <= end_ix; rix++)
        temp_arr[temp_ix++] = arr[rix];

    // Copy the temp array into arr
    for (int ix = start_ix, t_ix = 0; ix <= end_ix && t_ix < temp_ix; ix++, t_ix++)
        arr[ix] = temp_arr[t_ix];
    
    // free allocated memory
    free(temp_arr);
}

