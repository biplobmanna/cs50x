#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int get_points(char letter);
int calculate_score(char* word);

int main(void) {
    char* ipstr[2] = { NULL, NULL};
    size_t strsize[2]; 

    // Take str inputs (getline also takes \n into the input)
    printf("first word? : ");
    getline(&ipstr[0], &strsize[0], stdin);

    printf("second word? : ");
    getline(&ipstr[1], &strsize[1], stdin);

    // calculate scores
    int scores[2];
    scores[0] = calculate_score(ipstr[0]);
    scores[1] = calculate_score(ipstr[1]);

    // print the scores
    printf("Scores: [ %d, %d ]\n", scores[0], scores[1]);

    // declare winner
    if (scores[0] > scores[1]) 
        printf("first word is the winner!\n");
    else if (scores[1] > scores[0])
        printf("second word is the winner!\n");
    else
        printf("both words are equal, and both win!\n");

    return 0;
}

int calculate_score(char* word) {
    int score = 0;
    // the condition should also take into consideration the \n read by getline
    for(int i = 0, slen = strlen(word); i < slen && word[i] != '\n'; i++)
        score += get_points(word[i]);
    return score;
}

int get_points(char letter) {
    // check char isalpha and convert to uppercase
    if (isalpha(letter)) {
        int points_arr[] = \
            {1,	3,	3,	2,	1,	4,	2,	4,	1,	8,	5,	1,	3,	1,	1,	3,	10,	1,	1,	1,	1,	4,	4,	8,	4,	10};
        
        // convert to uppercase
        letter = toupper(letter);

        // index = letter_ascii - ascii('A')
        return points_arr[letter - 'A'];
    }
    else
        return 0;
}