#include <stdio.h>

/**
 * Greedy Algo:
 * Give the change to the customer, while making sure to give the minumum number of coins. 
 * Coins available are in cents: 1, 5, 10, 25
*/

// Count the coins <= the change
int count_coins(int coin, int change) {
    int count = 0;
    while ( coin * count <= change ) {
        count++;
    }
    return --count;
}

// Greedy algo: find the least number of coins
void find_least_change(int change) {
    int change_counts[4][2] = {
        // coin, count
        {25, 0},
        {10, 0},
        {5, 0},
        {1, 0}
    };
    int total_coins_count = 0;

    // find each change count
    for(int coins_ix = 0; coins_ix < 4 && change > 0; coins_ix++) {
        change_counts[coins_ix][1] = count_coins(change_counts[coins_ix][0], change);
        change -= change_counts[coins_ix][0] * change_counts[coins_ix][1];
        total_coins_count += change_counts[coins_ix][1];
    }
    printf("total count: %d\n", total_coins_count);
}

// take input from user, and use the above functions as logic
int main(void) {
    // Taking input as decimal values
    printf("change owed? ");
    float fchange;
    scanf("%f", &fchange);
    // Converting into integer coins
    int change = (int) (fchange * 100);

    find_least_change(change);
}