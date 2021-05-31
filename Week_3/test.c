#include <stdio.h>

int main(int argc, int **argv) {
    char *some = "some";
    char *thing = "thing";
    // swapping
    char *temp = some;
    some = thing;
    thing = temp;

    printf("%s, %s\n", some, thing);
}