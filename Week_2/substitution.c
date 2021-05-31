#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char substitution(char ch, char* str_substitution);
void encrypt(char* string, char* str_substitution);

int main(void) {
    char* string = NULL;
    char* str_substitution = NULL;
    size_t strsize, subsize;

    // take inputs
    printf("string? : ");
    getline(&string, &strsize, stdin);
    
    printf("substitution? : ");
    getline(&str_substitution, &subsize, stdin);

    // sanity checks
    if (strlen(str_substitution) != 27) {
        printf("Substitution string must be of length 26!\n");
        return -1;
    }

    // testing by printing the values
    encrypt(string, str_substitution);
    printf("\nencrypted string: %s\n", string);
}

void encrypt(char* string, char* str_substitution) {
    for(int i = 0, slen = strlen(string); i < slen && string[i] != '\n'; i++) {
        string[i] = substitution(string[i], str_substitution);
    }
}

char substitution(char ch, char* str_substitution) {
    if (!isalpha(ch))
        return ch;
    if (isupper(ch)) {
        return str_substitution[ ch - 'A' ];
    } else {
        return str_substitution[ ch - 'a' ];
    }
}