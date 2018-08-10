#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"

//test and failure counters
int failureCount = 0;
int testCount = 0;

//replaces c assert so that we can run through all tests even if they fail
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
    int i;
    int numPlayers = 2;
    int player0 = 0;
    int player1 = 1;

    int handpos = 0;
    int choice1 = 0, choice2 = 0, choice3 = 0;
    int bonus = 0;

    int k[10] = {adventurer, council_room, feast, gardens, mine,
               remodel, smithy, village, baron, great_hall};

    int seed = 2000;
    
    //inits structs for current state and original state for comparison
    struct gameState state, originalState;

    printf("Starting tests for smithyEffect()...\n");
    memset(&state,23,sizeof(struct gameState));
    memset(&originalState,23,sizeof(struct gameState));

    //starts game
    initializeGame(numPlayers, k, seed, &state);

    //copies current state so we can make changes and compare
    memcpy(&originalState, &state, sizeof(struct gameState));

    //calls function to test
    cardEffect(smithy, choice1, choice2, choice3, &state, handpos, &bonus);

    printf("\nTEST: Player 0 gains 3 cards\n");
    printf("Actual: %d\n",state.handCount[player0]);
    printf("Expected: %d\n",originalState.handCount[player0]+2);
    assertTrue(state.handCount[player0],originalState.handCount[player0]+2);

    printf("\nTEST: Player 0 gains 3 cards from his own pile\n");
    printf("Actual: %d\n",state.deckCount[player0]);
    printf("Expected: %d\n",originalState.deckCount[player0]-3);
    assertTrue(state.deckCount[player0],originalState.deckCount[player0]-3);

    printf("\nTEST: No change to victory card piles\n");
    
    printf("Province Pile\n");
    printf("Actual: %d\n",state.supplyCount[province]);
    printf("Expected: %d\n",originalState.supplyCount[province]);
    assertTrue(state.supplyCount[province],originalState.supplyCount[province]);
    
    printf("\nDuchy Pile\n");
    printf("Actual: %d\n",state.supplyCount[duchy]);
    printf("Expected: %d\n",originalState.supplyCount[duchy]);
    assertTrue(state.supplyCount[duchy],originalState.supplyCount[duchy]);
    
    printf("\nEstate Pile\n");
    printf("Actual: %d\n",state.supplyCount[estate]);
    printf("Expected: %d\n",originalState.supplyCount[estate]);
    assertTrue(state.supplyCount[estate],originalState.supplyCount[estate]);

    printf("\nTEST: No change to kingdom card piles\n");
    for (i = 0; i < 10; i++) {
        printf("checking card piles...\n");
        assertTrue(state.supplyCount[k[i]],originalState.supplyCount[k[i]]);
    }

    printf("\nTEST: Player 1 was not affected\n");
    
    printf("Hand Count\n");
    printf("Actual: %d\n",state.handCount[player1]);
    printf("Expected: %d\n",originalState.handCount[player1]);
    assertTrue(state.handCount[player1],originalState.handCount[player1]);
    
    printf("\nDeck Count\n");
    printf("Actual: %d\n",state.deckCount[player1]);
    printf("Expected: %d\n",originalState.deckCount[player1]);
    assertTrue(state.deckCount[player1],originalState.deckCount[player1]);

    if (failureCount) {
        printf("\nTEST(S) FAILED\n");
        printf("%d of %d tests failed!\n",failureCount,testCount);
    }
    else {
        printf("\nTESTS SUCCESSFULLY COMPLETED\n\n");
    }

    return 0;
}