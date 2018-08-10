#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"

//fails and tests counters
int failureCount = 0;
int testCount = 0;

//replaces c assert
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

//starts tests
int main () {
    
    //sets up game
    int numPlayers = 2;

    int k[10] = {adventurer, council_room, feast, gardens, mine,
               remodel, smithy, village, baron, great_hall};
    int seed = 2000;
    struct gameState state;

    printf("Starting tests for isGameOver()...\n");

    memset(&state,23,sizeof(struct gameState));
    initializeGame(numPlayers, k, seed, &state);

    state.supplyCount[province] = 0;

    printf("\nTEST: Province cards empty\n");
    printf("Actual: %d\n",isGameOver(&state));
    printf("Expected: %d\n",1);
    assertTrue(isGameOver(&state),1);

    state.supplyCount[province] = 1;

    state.supplyCount[0] = 0;
    state.supplyCount[1] = 0;
    state.supplyCount[2] = 0;

    printf("\nTEST: Three supply piles empty\n");
    printf("Actual: %d\n",isGameOver(&state));
    printf("Expected: %d\n",1);
    assertTrue(isGameOver(&state),1);

    state.supplyCount[0] = 1;
    state.supplyCount[1] = 1;
    state.supplyCount[2] = 1;

    printf("\nTEST: Province cards not empty\n");
    printf("\nTEST: Three supply piles not empty\n");
    printf("Actual: %d\n",isGameOver(&state));
    printf("Expected: %d\n",0);
    assertTrue(isGameOver(&state),0);

    if (failureCount) {
        printf("\nTEST(S) FAILED\n");
        printf("%d of %d tests failed!\n",failureCount,testCount);
    }
    else {
        printf("\nTESTS SUCCESSFULLY COMPLETED\n\n");
    }

    return 0;
}