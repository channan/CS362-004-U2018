#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"

//fail and test counters
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
    int i;
    int numPlayers = 2;
    int player0 = 0;
    int player1 = 1;

    int handpos = 0;
    int choice1 = copper, choice2 = silver, choice3 = 0;
    int bonus = 0;

    int k[10] = {adventurer, council_room, feast, gardens, mine,
               remodel, smithy, village, baron, great_hall};

    int seed = 2000;

    int handCount = 5;
    
    int coppers[MAX_HAND];
    int silvers[MAX_HAND];
    int golds[MAX_HAND];

    //fills hand with designated treasure
    for (i = 0; i < MAX_HAND; i++) {
        coppers[i] = copper;
        silvers[i] = silver;
        golds[i] = gold;
    }

    //multiples structs for comparison
    struct gameState state, originalState;

    printf("Starting tests for mineEffect()...\n");
    memset(&state,23,sizeof(struct gameState));
    memset(&originalState,23,sizeof(struct gameState));

    //starts game
    initializeGame(numPlayers, k, seed, &state);

    //copies state for comparison
    memcpy(&originalState, &state, sizeof(struct gameState));

    //fills hand with coppers
    memcpy(state.hand[player0],coppers,sizeof(int)*handCount);

    //calls function for testing
    cardEffect(mine, choice1, choice2, choice3, &state, handpos, &bonus);

    printf("\nTEST: Player 0 hand count is unaffected\n");
    printf("Actual: %d\n",state.handCount[player0]);
    printf("Expected: %d\n",originalState.handCount[player0]);
    assertTrue(state.handCount[player0],originalState.handCount[player0]);

    printf("\nTEST: Player 0 deck count is unaffected\n");
    printf("Actual: %d\n",state.deckCount[player0]);
    printf("Expected: %d\n",originalState.deckCount[player0]);
    assertTrue(state.deckCount[player0],originalState.deckCount[player0]);

    printf("\nTEST: No change to victory card piles\n");
    
    printf("Province Pile\n");
    printf("Actual: %d\n",state.supplyCount[province]);
    printf("Expected: %d\n",originalState.supplyCount[province]);
    assertTrue(state.supplyCount[province],originalState.supplyCount[province]);
    
    printf("Duchy Pile\n");
    printf("Actual: %d\n",state.supplyCount[duchy]);
    printf("Expected: %d\n",originalState.supplyCount[duchy]);
    assertTrue(state.supplyCount[duchy],originalState.supplyCount[duchy]);
    
    printf("Estate Pile\n");
    printf("Actual: %d\n",state.supplyCount[estate]);
    printf("Expected: %d\n",originalState.supplyCount[estate]);
    assertTrue(state.supplyCount[estate],originalState.supplyCount[estate]);

    printf("\nTEST: Player 1 was not affected\n");
    
    printf("Hand Count\n");
    printf("Actual: %d\n",state.handCount[player1]);
    printf("Expected: %d\n",originalState.handCount[player1]);
    assertTrue(state.handCount[player1],originalState.handCount[player1]);
    
    printf("Deck Count\n");
    printf("Actual: %d\n",state.deckCount[player1]);
    printf("Expected: %d\n",originalState.deckCount[player1]);
    assertTrue(state.deckCount[player1],originalState.deckCount[player1]);

    printf("\nTEST: No change to kingdom card piles\n");
    for (i = 0; i < 10; i++) {
        printf("checking card piles...\n");
        assertTrue(state.supplyCount[k[i]],originalState.supplyCount[k[i]]);
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