#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// -----------------------------------------------------
// declare the structures and their including functions
// -----------------------------------------------------

// candidate template
typedef struct candidate {
    char *name;
    int vote_count;
    // functions
    char* (*create_string)(char*);
    void (*free_string_memory)(char*);
} candidate;

// voters template
typedef struct voter {
    char *vote1;
    char *vote2;
    char *vote3;
    // functions
    char* (*create_string)(char*);
    void (*free_string_memory)(char*);
} voter;

// define those functions
char* create_string(char* str) {
    // allocate memory and copy the str to it
    int len = strlen(str);
    char *new_str = malloc((len + 1) * sizeof(char));
    // copy
    for(int i=0; str[i] != '\0' && str[i] != '\n'; i++) { new_str[i] = str[i]; }
    new_str[len] = '\0'; // terminate char[] with '\0' to be considered a string

    return new_str;
}
void free_string_memory(char* str) { free(str); }

// -----------------------------------------------------
// functions declarations
// -----------------------------------------------------
int free_candidate_memory(candidate* candidate_list);
int free_voter_memory(voter* voter_list);
void take_voter_input(const ssize_t voter_count, voter* voter_list, candidate* candidate_list);
int is_valid_candidate(char* name, candidate* candidate_list);

// -----------------------------------------------------
// functions definitions
// -----------------------------------------------------

// the main function
int main(int argc, char **argv) {
    // arguments basic check
    if (argc <= 1) { printf("atleast one candidate name is required...\n"); return 1; }

    // create the candidates
    candidate *candidate_list = malloc((argc - 1) * sizeof(candidate));
    for(int i = 0; i < argc - 1; i++) {
        // link those functions
        candidate_list[i].create_string = &create_string;
        candidate_list[i].free_string_memory = &free_string_memory;

        // add the names & votes
        candidate_list[i].name =  candidate_list[i].create_string(argv[i + 1]);
        candidate_list[i].vote_count = 0;
    }

    // create the voters
    ssize_t no_of_voters;
    scanf("%d", &no_of_voters);
    getchar(); // discard the '\n' character

    // voters
    voter *voter_list = malloc(no_of_voters * sizeof(voter_list));


}

// ----------------------------------------
// other functions
// ----------------------------------------
void take_voter_input(const ssize_t voter_count, voter* voter_list, candidate* candidate_list) {
    for (int i = 0; i < voter_count; i++) {
        // link the functions
        voter_list[i].create_string = &create_string;
        voter_list[i].free_string_memory = &free_string_memory;
        // how many inputs to take?
        // check if the current input isn't the same as previous input
        // check if the input contains the candidates also
    }
}
int free_candidate_memory(candidate* candidate_list);
int free_voter_memory(voter* voter_list);
