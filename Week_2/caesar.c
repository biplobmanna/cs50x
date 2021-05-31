#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char caesarshift(char ch, int shift);
void encrypt(char* string, int shift);

int main(void) {
    char* string = NULL;
    size_t strsize;
    int shift_num;

    // take inputs
    printf("string? : ");
    getline(&string, &strsize, stdin);
    
    printf("shift by? : ");
    scanf("%d", &shift_num);

    // testing by printing the values
    encrypt(string, shift_num);
    printf("\nencrypted string: %s\n", string);
}

void encrypt(char* string, int shift) {
    for(int i = 0, slen = strlen(string); i < slen && string[i] != '\n'; i++) {
        if (isalpha(string[i]))
            string[i] = caesarshift(string[i], shift);
    }
}

char caesarshift(char ch, int shift) {
    int alpha_position;
    if (isupper(ch)) {
        alpha_position = ((ch - 'A') + shift) % 26;
        return alpha_position + 'A';
    } else {
        alpha_position = ((ch - 'a') + shift) % 26;
        return alpha_position + 'a';
    }
}