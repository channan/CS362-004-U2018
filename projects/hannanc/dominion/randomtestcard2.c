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
int numBuysFails = 0;
int otherPlayerDeckHandFails = 0;

void checkCouncilRoomEffect(int p, struct gameState *post);

int main ()
{
    printf("RANDOM TEST - councilRoomEffect()\n");

    int iterations = 10000;
    int i, n, player, deckCount, handCount, discardCount;
    int numberOfPlayers[] = {2,3,4};
    struct gameState G;
    srand(time(NULL));

    //randomly inits the gamestate, code is from the lecture notes
    for (n = 0; n < iterations; n++)
    {
        for (i = 0; i < sizeof(struct gameState); i++)
        {
            ((char*)&G)[i] = floor(Random() * 256);
        }

        //randomly sets different game variables
        G.numPlayers = numberOfPlayers[rand() % 3];
        G.numBuys = 1;
        G.playedCardCount = floor(Random() * (MAX_DECK-1));
        player = G.numPlayers - 2;
        deckCount = floor(Random() * MAX_DECK);
        handCount = floor(Random() * MAX_HAND);
        discardCount = floor(Random() * MAX_DECK);
        G.whoseTurn = player;

        //sets the hand and deck values for the other players
        for (i = 0; i < G.numPlayers; i++)
        {
            G.deckCount[i] = deckCount;
            G.handCount[i] = handCount;
            G.discardCount[i] = discardCount;
        }

        checkCouncilRoomEffect(player,&G);
    }

    //tallies up the fail counts
    int totalFails = cardEffectFails + discardCardFails + drawCardFails + deckHandCountFails + numBuysFails;

    //prints the test results
    printf("\nRESULTS\n");
    printf("PASSED: %d\n",iterations - totalFails);
    printf("FAILED: %d\n",totalFails);

    if (totalFails == 0)
    {
        printf ("RANDOM TEST PASSED\n\n");
    }
    else
    {
        printf("\nRANDOM TEST FAILED\n");
        printf("\nREPORT\n");
        printf("drawCard() failed: %d\n",drawCardFails);
        printf("cardEffect() failed: %d\n",cardEffectFails);
        printf("discardCard() failed: %d\n",discardCardFails);
        printf("numBuys Count mismatch: %d\n",numBuysFails);
        printf("Other players hand/deck count mismatch: %d\n",otherPlayerDeckHandFails);
        printf("Selected player hand/deck count mismatch: %d\n\n",deckHandCountFails);
    }

    //coverage is displayed next as part of make rule
    printf ("COVERAGE\n");
    return 0;
}

void checkCouncilRoomEffect(int p, struct gameState *post)
{
    int r,s,t,u,v,w,x,i;
    int bonus = 0;

    //gamestate variable to store previous state
    struct gameState pre;

    //which is copied into a post state gamestate variable
    memcpy(&pre,post,sizeof(struct gameState));

    //calls the council room card effect function
    r = cardEffect(council_room,0,0,0,post,0,&bonus);

    //calls drawcard function 4 times
    s = drawCard(p,&pre);
    t = drawCard(p,&pre);
    u = drawCard(p,&pre);
    v = drawCard(p,&pre);

    pre.numBuys++;

    //the other players each draw a card
    for (i = 0; i < pre.numPlayers; i++)
    {
        if (i != p)
        {
            w = drawCard(i,&pre);

            //checks if the drawcard failed
            if (w == -1 && pre.deckCount[i] != 0)
            {
                drawCardFails++;
            }
        }
    }

    x = discardCard(0, p, &pre, 0);

    //gets values for hand and deck counts
    int postHC = post->handCount[p];
    int postDC = post->deckCount[p];
    int preHC = pre.handCount[p];
    int preDC = pre.deckCount[p];

    //checks if the number of buys match
    if (pre.numBuys != post->numBuys)
    {
        numBuysFails++;
    }

    //checks if draw card failed
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

    if (v == -1 && pre.deckCount[p] != 0)
    {
        drawCardFails++;
    }

    //checks if cardeffect or discardcard fails
    if (!(r == 0 && x == 0))
    {
        if (r)
        {
            cardEffectFails++;
        }

        if (x)
        {
            discardCardFails++;
        }
    }

    //checks if the hand and deck counts matchup or not
    if (!(postHC == preHC && postDC == preDC))
    {
        deckHandCountFails++;
    }

    //checks if the other players hand and deck counts matchup or not
    for (i = 0; i < pre.numPlayers; i++)
    {
        if (i != p)
        {
            if (!(post->handCount[i] == pre.handCount[i] && post->deckCount[i] == pre.deckCount[i]))
            {
                otherPlayerDeckHandFails++;
            }
        }
    }
}