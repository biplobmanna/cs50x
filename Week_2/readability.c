#include "coleman_liam_index.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    char* string = NULL;
    size_t str_size;

    // take input
    printf("Enter your line below:\n");
    getline(&string, &str_size, stdin);

    printf("\nColeman-Liam Index: %d\n", find_readability_index(string));
}

// Can run tests on this
// link: https://cs50.harvard.edu/x/2021/psets/2/readability/#how-to-test-your-code