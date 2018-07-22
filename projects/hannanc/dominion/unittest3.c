#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"

// global count of test failures
int failureCount = 0;
int testCount = 0;

// function to check if two ints are equal or not
void assertTrue(int a, int b) {
    if (a == b) {
        printf("PASSED\n");
        testCount++;
    }
    else {
        printf("FAILED\n");
        failureCount++;
        testCount++;
    }
}

// runs the tests
int main () {
    int numPlayers = 2;
    int player = 0;

    // kingdom cards
    int k[10] = {adventurer, council_room, feast, gardens, mine,
               remodel, smithy, village, baron, great_hall};
    int seed = 2000;
    struct gameState state;

    printf("Starting tests for shuffle()...\n");
    memset(&state,23,sizeof(struct gameState));
    initializeGame(numPlayers, k, seed, &state);

    state.deckCount[player] = 0;
    printf("\nTEST: Player deck count is 0\n");
    printf("Actual: %d\n",shuffle(player,&state));
    printf("Expected: %d\n",-1);
    assertTrue(shuffle(player,&state),-1);

    printf("\nTEST: Player deck count is 10 before and after shuffle\n");
    state.deckCount[player] = 10;
    shuffle(player,&state);
    printf("Actual: %d\n",state.deckCount[player]);
    printf("Expected: %d\n",10);
    assertTrue(state.deckCount[player],10);

    printf("\nTEST: Cards are shuffled\n");
    int pre_shuffle_card = state.deck[player][0];
    shuffle(player,&state);
    int post_shuffle_card = state.deck[player][0];
    if (pre_shuffle_card != post_shuffle_card) {
        printf("Actual: %d\n",1);
        printf("Expected: %d\n",1);
        assertTrue(1,1);
    }
    else {
        printf("Actual: %d\n",0);
        printf("Expected: %d\n",1);
        assertTrue(0,1);
    }

    if (failureCount) {
        printf("\nTEST(S) FAILED\n");
        printf("%d of %d tests failed!\n",failureCount,testCount);
    }
    else {
        printf("\nTESTS SUCCESSFULLY COMPLETED\n\n");
    }

    return 0;
}