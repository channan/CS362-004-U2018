#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"

//sets up counters for tests
int failureCount = 0;
int testCount = 0;

//replaces assert so that code can still compile with failing tests
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

int main () {
    
    //sets up game
    int i;
    int treasureCount = 0;
    int treasureCountOriginal = 0;
    int numPlayers = 2;
    int player0 = 0;
    int player1 = 1;
    int card;
    int handpos = 0;
    int choice1 = 0, choice2 = 0, choice3 = 0;
    int bonus = 0;

    int k[10] = {adventurer, council_room, feast, gardens, mine,
               remodel, smithy, village, baron, great_hall};

    int seed = 2000;

    //inits structs for two games states to compare
    struct gameState state, originalState;
  
    //starts tests
    printf("Starting tests for adventurerEffect()...\n");
    memset(&state,23,sizeof(struct gameState));
    memset(&originalState,23,sizeof(struct gameState));

    //starts game in one of states
    initializeGame(numPlayers, k, seed, &state);

    //copies the game to the other state for comparison
    memcpy(&originalState, &state, sizeof(struct gameState));

    //calls function to test
    cardEffect(adventurer, choice1, choice2, choice3, &state, handpos, &bonus);

    printf("\nTEST: Player 0 gains 2 cards\n");
    printf("Actual: %d\n",state.handCount[player0]);
    printf("Expected: %d\n",originalState.handCount[player0]+2);
    assertTrue(state.handCount[player0],originalState.handCount[player0]+2);

    //checks how much treasure is gained
    for (i = 0; i < state.handCount[player0]; i++) {
        card = state.hand[player0][i];
        if (card == copper || card == silver || card == gold) {
            treasureCount++;
        }
    }

    //checks default treasure count
    for (i = 0; i < originalState.handCount[player0]; i++) {
        card = originalState.hand[player0][i];
        if (card == copper || card == silver || card == gold) {
            treasureCountOriginal++;
        }
    }

    //compares game state and its copy
    printf("\nTEST: Player 0 gains 2 treasure cards\n");
    
    printf("Actual: %d\n",treasureCount);
    printf("Expected: %d\n",treasureCountOriginal+2);
    assertTrue(treasureCountOriginal+2,treasureCount);

    printf("\nTEST: No changes to victory card piles\n");
    
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

    printf("\nTEST: No changes to kingdom card piles\n");
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