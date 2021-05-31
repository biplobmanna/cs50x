#include <stdio.h>

int print_space(int n) {
    for(int iter=0; iter < n; iter++) {
        printf(" ");
    }
}
int print_symbol(char sym, int times) {
    for(int iter = 0; iter < times; iter++) {
        printf("%c", sym);
    }
}
int main(void) {
    // input wall height
    int wall_height;
    printf("Wall height? ");
    scanf("%d", &wall_height);

    // Since each line starts with spaces, followed by a character
    // max_space_required will be the max space that is requried to be printed
    int max_space_required = wall_height - 1;
    for(int row = 0; row < wall_height; row++) {
        // 1st: print the required spaces
        print_space(max_space_required - row);
        // 2nd: print the symbols
        print_symbol('#', row + 1);
        // 3rd: print space
        print_space(2);
        // 4th: print the symbols again
        print_symbol('#', row + 1);
        // newline
        printf("\n");
    }
}