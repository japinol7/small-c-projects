#include "count_coins.h"
#include <stdlib.h>

// Coin values in cents
#define NUM_COINS 4
static const int coin_values[NUM_COINS] = {
    25, // quarters
    10, // dimes
    5,  // nickels
    1,  // pennies
};

// Calculate the number of ways to make change for a given amount
int count_coins_changes(const int amount) {
    // Handle invalid input
    if (amount < 1) {
        return 0;
    }

    // Allocate array to store number of ways for each amount
    int* ways = (int*)calloc(amount + 1, sizeof(int));
    if (!ways) {
        return -1; // Memory allocation failed
    }

    // Base case: there's 1 way to make change for 0 cents: using no coins
    ways[0] = 1;

    // For each coin type
    for (int i = 0; i < NUM_COINS; i++) {
        int coin = coin_values[i];
        // For each amount from coin value to target amount
        for (int j = coin; j <= amount; j++) {
            ways[j] += ways[j - coin];
        }
    }

    const int result = ways[amount];
    free(ways);
    return result;
}
