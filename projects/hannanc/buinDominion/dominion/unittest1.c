#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"

//test and fail counters
int failureCount = 0;
int testCount =0;

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

//runs tests
int main () {
    
    //sets up game
    int i, b;
    int numPlayers = 2;
    int player = 0;

    int k[10] = {adventurer, council_room, feast, gardens, mine,
               remodel, smithy, village, baron, great_hall};
    int seed = 2000;
    struct gameState state;
    int handCount;
    int bonus = 1;

    int coppers[MAX_HAND];
    int silvers[MAX_HAND];
    int golds[MAX_HAND];

    //fills hand with designated treasure
    for (i = 0; i < MAX_HAND; i++) {
        coppers[i] = copper;
        silvers[i] = silver;
        golds[i] = gold;
    }

    printf("Starting tests for updateCoins()...");

    //tests how updateCoins handles each treasure as well as a different bonus and hand count
    for (handCount = 0; handCount <= 5; handCount = handCount + 5) {
        printf("\n\nTreasure cards: %d\n",handCount);
        printf("Bonus: %d\n", bonus);

        memset(&state,23,sizeof(struct gameState));
        b = initializeGame(numPlayers, k, seed, &state);
        state.handCount[player] = handCount;

        //fills hand with coppers
        memcpy(state.hand[player],coppers,sizeof(int)*handCount);
        updateCoins(player,&state,bonus);

        printf("\nTEST: Coin Count - copper\n");
        printf("Actual: %d\n",state.coins);
        printf("Expected: %d\n",handCount*1+bonus);
        assertTrue(state.coins,handCount*1+bonus);

        //fills hand with silvers
        memcpy(state.hand[player],silvers,sizeof(int)*handCount);
        updateCoins(player,&state,bonus);

        printf("\nTEST: Coin Count - silver\n");
        printf("Actual: %d\n",state.coins);
        printf("Expected: %d\n",handCount*2+bonus);
        assertTrue(state.coins,handCount*2+bonus);

        //fills hand with golds
        memcpy(state.hand[player],golds,sizeof(int)*handCount);
        updateCoins(player,&state,bonus);

        printf("\nTEST: Coin Count - gold\n");
        printf("Actual: %d\n",state.coins);
        printf("Expected: %d\n",handCount*3+bonus);
        assertTrue(state.coins,handCount*3+bonus);

        bonus = bonus + 2;
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