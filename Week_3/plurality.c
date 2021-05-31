/*
    Complete the implementation of plurality.c in such a way that the program simulates a plurality vote election.
        Complete the vote function.
        ----------------------------
            vote takes a single argument, a string called name, representing the name of the candidate who was voted for.
            If name matches one of the names of the candidates in the election, then update that candidate’s vote total to account for the new vote. The vote function in this case should return true to indicate a successful ballot.
            If name does not match the name of any of the candidates in the election, no vote totals should change, and the vote function should return false to indicate an invalid ballot.
            You may assume that no two candidates will have the same name.
        Complete the print_winner function.
        -----------------------------------
            The function should print out the name of the candidate who received the most votes in the election, and then print a newline.
            It is possible that the election could end in a tie if multiple candidates each have the maximum number of votes. In that case, you should output the names of each of the winning candidates, each on a separate line.
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

// define the candidate datatype structure
// char pointer isn't the same as creating a character array inside the struct
// also using function pointers
typedef struct candidate{
    char* name;
    int vote_count;
    // create the name array
    char* (*set_name)(int, char*);
    // free the name array
    void (*free_name_memory)(char*);
} candidate;

// create the struct functions
char* set_name(int len, char* str){
    char *name = malloc((len + 1) * sizeof(char));
    strcpy(name, str);
    return name;
}
void free_name_memory(char *name) { free(name); }

// ---------------------------------------------------------------------
// Functions prototypes
// ---------------------------------------------------------------------
// take votes input by name
void vote_input(candidate* candidate_list, const int candidate_count);
// take valid names as input
int find_candidate_index(const candidate* candidate_list, const int candidate_count, const char* candidate_name);
// sort the final result
void sort_result(candidate* candidate_list, const int start, const int end);
// merge
void merge(candidate* candidate_list, const int start, const int mid, const int end);
// print the candidate details
void print_candidate_details(const candidate* candidate_list, const int candidate_count);
// test the storing of names into pointers
void test(candidate* candidate_list, const int start, const int end);
// -----------------------------------------------------------------------
// All functions
// -----------------------------------------------------------------------
int main(int argc, char** argv) {
    // check enough command line inputs are there
    if (argc <= 1) { printf("Not enough arguments!\n"); return 1; }

    // allocate enough memory for candidate_list array
    candidate *candidate_list = malloc((argc - 1) * sizeof(candidate));
    // initialize
    // link all the functions & store the values
    for (int ix = 0; ix < argc - 1; ix++) {
        // assign the function pointers
        candidate_list[ix].set_name = set_name;
        candidate_list[ix].free_name_memory = free_name_memory;

        // store the values
        candidate_list[ix].name =  candidate_list[ix].set_name(strlen(argv[ix + 1]), argv[ix + 1]);
        candidate_list[ix].vote_count = 0;
    }
    
    // print the details
    print_candidate_details(candidate_list, argc - 1);

    // take vote input
    vote_input(candidate_list, argc - 1);

    // test storing of names into char array
    // test(candidate_list, 0, argc - 2);

    // sort the results
    sort_result(candidate_list, 0, argc - 2);

    // print the sorted result
    print_candidate_details(candidate_list, argc - 1);

    // free the memory
    for (int ix = 0; ix < argc - 1; ix++)
        candidate_list[ix].free_name_memory(candidate_list[ix].name);
    free(candidate_list);
}

// print the candidate details
void print_candidate_details(const candidate* candidate_list, const int candidate_count) {
    printf("\n** Candidate Votes **\n------------------------\n");
    for (int ix = 0; ix < candidate_count; ix++) 
        printf("* %s : %d\n", candidate_list[ix].name, candidate_list[ix].vote_count);
}

// take votes input by name
void vote_input(candidate* candidate_list, const int candidate_count){
    int no_of_voters;
    printf("\n** Voting **\n------------------------\nNo of voters? : ");
    scanf("%d", &no_of_voters); 
    getchar(); // to remove the dummy \n -- stupid error caused by scanf()

    // take votes
    char candidate_ix = -1; // input valid flag
    char *vote_candidate_name = NULL; // input string
    ssize_t input_line_size; // size of the input string
    // take the votes
    for (int ix = 0; ix < no_of_voters; ix++) {
        while(candidate_ix < 0) { // keep taking input until a valid vote is cast
            printf("%d>> vote for? : ", ix + 1);
            getline(&vote_candidate_name, &input_line_size, stdin);
            // since getline also takes in \n as input, it would be better to just remove that
            vote_candidate_name[strlen(vote_candidate_name) - 1] = '\0'; // shorten the length by 1

            // find index of the candidate whose name is entered in the candidate_list
            candidate_ix = find_candidate_index(candidate_list, candidate_count, vote_candidate_name);

            // free heap memory allocated by getline
            free(vote_candidate_name);
            vote_candidate_name = NULL;
        }

        // update the vote count
        candidate_list[candidate_ix].vote_count++;
        // reset the candidate index
        candidate_ix = -1;
    }
}

// take valid names as input
int find_candidate_index(const candidate* candidate_list, const int candidate_count, const char* candidate_name) {
    // do some basic redundancy checks
    if (candidate_name == NULL) { printf("!! invalid input !!\n"); return -1; }

    for (int ix = 0; ix < candidate_count; ix++) {
        // check if any name matches the input
        if(strcmp(candidate_list[ix].name, candidate_name) == 0)
            return ix;
    }
    printf("!! invalid input !!\n");
    return -1;
}
// sort the final result
void sort_result(candidate* candidate_list, const int start, const int end) {
    if (end - start <= 0) return;

    int mid = (start + end) / 2;

    sort_result(candidate_list, start, mid);
    sort_result(candidate_list, mid + 1, end);

    merge(candidate_list, start, mid, end);
}
// merge function as part of the merge-sort
void merge(candidate* candidate_list, const int start, const int mid, const int end) {
    char **names_list = malloc((end - start + 1) * sizeof(char*)); // store an array of pointers
    int *votes_list = malloc((end - start + 1) * sizeof(int));
    int votes_list_ix = 0, left_ix = start, right_ix = mid + 1;
    // use index instead of storing the data
    // make a logic to swap the values properly
    // take extra care for pointers -- test out pointers
    while(left_ix <= mid && right_ix <= end) {
        if(candidate_list[left_ix].vote_count >= candidate_list[right_ix].vote_count) {
            votes_list[votes_list_ix] = candidate_list[left_ix].vote_count;
            names_list[votes_list_ix] = candidate_list[left_ix].name;
            left_ix++; votes_list_ix++;
        }
        else {
            votes_list[votes_list_ix] = candidate_list[right_ix].vote_count;
            names_list[votes_list_ix] = candidate_list[right_ix].name;
            right_ix++; votes_list_ix++;
        }
    }
    // copy the rest
    for(;left_ix <= mid; left_ix++, votes_list_ix++) { 
        votes_list[votes_list_ix] = candidate_list[left_ix].vote_count;
        names_list[votes_list_ix] = candidate_list[left_ix].name; 
    }
    for(;right_ix <= end; right_ix++, votes_list_ix++) { 
        votes_list[votes_list_ix] = candidate_list[right_ix].vote_count;
        names_list[votes_list_ix] = candidate_list[right_ix].name;
    }

    // copy it back to the original array
    for(int cl_ix = start, vl_ix = 0; cl_ix <= end && vl_ix < votes_list_ix; cl_ix++, vl_ix++) {
        candidate_list[cl_ix].name = names_list[vl_ix];
        candidate_list[cl_ix].vote_count = votes_list[vl_ix];
    }

    // free heap allocation
    free(votes_list);
    free(names_list);
}


// testing memory allocation for storing char*
void test(candidate* candidate_list, const int start, const int end) {
    printf("\n** inside test...\n-------------------------------\n");

    char **names = malloc((end - start + 1) * sizeof(char*)); // array of char pointers
    for (int ix = start; ix <= end; ix++){
        names[ix - start] = candidate_list[ix].name;
    }

    for(int ix = start; ix <= end; ix++) {
        printf("** %s\n", names[ix - start]);
        // free(names[ix - start]);
    }
    // free(names);
}