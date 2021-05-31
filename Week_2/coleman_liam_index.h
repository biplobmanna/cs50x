#include <ctype.h>
#include <math.h>
#include <stdio.h>

int find_readability_index(char* string);
int calculate_coleman_liam_index(int letters, int words, int sentences);

int find_readability_index(char* string) {
    int letter_count = 0;
    int word_count = 0;
    int sentence_count = 0;

    // read char-wise and calculate count of everything
    for (int i=0; string[i] != '\0'; i++) {
        if (isalpha(string[i]))
            letter_count++;
        else if (isspace(string[i]) || string[i] == '\n') 
            word_count++;
        else if (string[i] == '.' || string[i] == '!' || string[i] == '?')
            sentence_count++;
    }
    printf("letters: %d, words: %d, sentences: %d\n", letter_count, word_count, sentence_count);

    return calculate_coleman_liam_index(letter_count, word_count, sentence_count);
}

int calculate_coleman_liam_index(int letters, int words, int sentences) {
    float avg_letters_per_100_words = ((float) letters / words) * 100.0;
    float avg_sentences_per_100_words = ((float) sentences / words) * 100.0;

    float index = (0.0588 * avg_letters_per_100_words) \
                    - (0.296 * avg_sentences_per_100_words) - 15.8;
    
    printf("index: %f\n", index);
    return (int) roundf(index);
}