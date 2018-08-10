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
    // kingdom cards
    int k[10] = {adventurer, council_room, feast, gardens, mine,
               remodel, smithy, village, baron, great_hall};
    int seed = 2000;
    struct gameState state;

    printf("Starting test for gainCard()...\n");
    
    memset(&state,23,sizeof(struct gameState));
    initializeGame(2, k, seed, &state);

    printf("\nTEST: Gold supply pile is empty\n");
    
    state.supplyCount[gold] = 0;
    
    printf("Actual: %d\n",gainCard(gold,&state,0,0));
    printf("Expected: %d\n",-1);
    assertTrue(gainCard(gold,&state,0,0),-1);
    
    state.supplyCount[gold] = 30;

    printf("\nTEST: Add card to deck\n");
    
    int deckCount = state.deckCount[0];
    gainCard(gold,&state,1,0);
    
    printf("Actual: %d\n",state.deckCount[0]);
    printf("Expected: %d\n",deckCount+1);
    assertTrue(deckCount+1,state.deckCount[0]);

    printf("\nTEST: Add card to hand\n");
    
    int handCount = state.handCount[0];
    gainCard(gold,&state,2,0);
    
    printf("Actual: %d\n",state.handCount[0]);
    printf("Expected: %d\n",handCount+1);
    assertTrue(handCount+1,state.handCount[0]);

    printf("\nTEST: Add card to discard pile\n");
    
    int discardCount = state.discardCount[0];
    gainCard(gold,&state,0,0);
    
    printf("Actual: %d\n",state.discardCount[0]);
    printf("Expected: %d\n",discardCount+1);
    assertTrue(discardCount+1,state.discardCount[0]);

    printf("\nTEST: Decrease gold supply\n");
    
    int goldSupply = state.supplyCount[gold];
    gainCard(gold,&state,0,0);
    
    printf("Actual: %d\n",state.supplyCount[gold]);
    printf("Expected: %d\n",goldSupply-1);
    assertTrue(goldSupply-1,state.supplyCount[gold]);

    if (failureCount) {
        printf("\nTEST(S) FAILED\n");
        printf("%d of %d tests failed!\n",failureCount,testCount);
    }
    else {
        printf("\nTESTS SUCCESSFULLY COMPLETED\n\n");
    }

    return 0;
}