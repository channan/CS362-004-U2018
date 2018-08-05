#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

//fail counters
int cardEffectFails = 0;
int discardCardFails = 0;
int drawCardFails = 0;
int deckHandCountFails = 0;

void checkSmithyEffect(int p, struct gameState *post);

int main ()
{
    printf("RANDOM TEST - smithyEffect()\n");

    int iterations = 10000;
    int i, n, player;
    struct gameState G;
    srand(time(NULL));

    //randomly inits a gamestate
    for (n = 0; n < iterations; n++)
    {
        for (i = 0; i < sizeof(struct gameState); i++)
        {
            ((char*)&G)[i] = floor(Random() * 256);
        }

        //randomly selects game variables
        player = floor(Random() * MAX_PLAYERS);
        G.deckCount[player] = floor(Random() * MAX_DECK);
        G.discardCount[player] = floor(Random() * MAX_DECK);
        G.handCount[player] = floor(Random() * MAX_HAND);
        G.playedCardCount = floor(Random() * (MAX_DECK-1));
        G.whoseTurn = player;

        //calls the test function
        checkSmithyEffect(player,&G);
    }

    //tallies up the total number of fails
    int totalFails = cardEffectFails + discardCardFails + drawCardFails + deckHandCountFails;

    //displays the results
    printf("\nRESULTS\n");
    printf("PASSED: %d\n",iterations - totalFails);
    printf("FAILED: %d\n",totalFails);

    if (totalFails == 0)
    {
        printf ("RANDOM TEST PASSED\n\n");
    }
    else
    {
        printf ("\nRANDOM TEST FAILED\n");
        printf("\nREPORT\n");
        printf("drawCard() failed: %d\n",drawCardFails);
        printf("cardEffect() failed: %d\n",cardEffectFails);
        printf("discardCard() failed: %d\n",discardCardFails);
        printf("Hand/Deck Count mismatch: %d\n\n",deckHandCountFails);
    }

    //coverage is displayed next in the .out so the title is placed here
    printf ("COVERAGE\n");
    return 0;
}

void checkSmithyEffect(int p, struct gameState *post)
{
    int r,s,t,u,v;

    //gamestate variable to store previous state
    struct gameState pre;

    //which is copied into a post state gamestate variable
    memcpy(&pre,post,sizeof(struct gameState));
    int bonus = 0;

    //call the smithyEffect function
    r = cardEffect(smithy,0,0,0,post,0,&bonus);

    //calls draw card 3 times
    s = drawCard(p,&pre);
    t = drawCard(p,&pre);
    u = drawCard(p,&pre);

    v = discardCard(0, p, &pre, 0);

    //gets the count values for hand and deck
    int postHC = post->handCount[p];
    int postDC = post->deckCount[p];
    int preHC = pre.handCount[p];
    int preDC = pre.deckCount[p];

    //checks if any of the drawcards failed
    if (s == -1 && pre.deckCount[p] != 0)
    {
        drawCardFails++;
    }

    if (t == -1 && pre.deckCount[p] != 0)
    {
        drawCardFails++;
    }

    if (u == -1 && pre.deckCount[p] != 0)
    {
        drawCardFails++;
    }

    //checks if cardeffect and discard failed
    if (!(r == 0 && v == 0))
    {
        if (r)
        {
            cardEffectFails++;
        }

        if (v)
        {
            discardCardFails++;
        }
    }

    //checks if the hand and deck counts didn't match up
    if (!(postHC == preHC && postDC == preDC))
    {
        deckHandCountFails++;
    }
}