#include<stdio.h>

#define MAX_STR_LENGTH 50

int main(void) {
    char name[MAX_STR_LENGTH];
    printf("What do I call you by? ");
    // scanf("%s", name);
    fgets(name, MAX_STR_LENGTH, stdin); // also takes the LF in the input
    printf("Hello, %s", name);
    return 0;
}
