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
int shuffleFails = 0;
int drawCardFails = 0;
int deckHandCountFails = 0;
int treasureCountFails = 0;

void checkAdventurerEffect(int p, struct gameState *post);

int main ()
{
    printf("RANDOM TEST - adventurerEffect()\n");
    int iterations = 10000;
    int treasures[] = {copper,silver,gold};
    int numTreasures;
    int i, n, player;
    struct gameState G;

    int min = 3;
    srand(time(NULL));

    //randomly inits the gamestate, this is from the lecture notes
    for (n = 0; n < iterations; n++)
    {
        for (i = 0; i < sizeof(struct gameState); i++)
        {
            ((char*)&G)[i] = floor(Random() * 256);
        }

        //randomly selects game variables
        player = floor(Random() * MAX_PLAYERS);
        G.deckCount[player] = floor(Random() * ((MAX_DECK - min) + 1) + min);
        numTreasures = floor(Random() * ((G.deckCount[player] - min) + 1) + min);

        //puts a least 3 treasure cards in the deck to be drawn
        for (i = 0; i < numTreasures; i++)
        {
            G.deck[player][i] = treasures[rand() % 3];
        }

        G.discardCount[player] = 0;
        G.handCount[player] = floor(Random() * ((MAX_HAND - min) + 1) + min);
        G.whoseTurn = player;

        //calls the test function
        checkAdventurerEffect(player, &G);
    }

    //tallies the total number of fails
    int totalFails = cardEffectFails + drawCardFails + shuffleFails + deckHandCountFails + treasureCountFails;

    //prints the results
    if (iterations - totalFails <= 0)
    {
        printf("\nRESULTS\n");
        printf("PASSED: %d\n",0);
        printf("FAILED: %d\n",iterations);
    }
    else
    {
        printf("\nRESULTS\n");
        printf("PASSED: %d\n",iterations - totalFails);
        printf("FAILED: %d\n",totalFails);
    }

    if (totalFails == 0) {
        printf ("RANDOM TEST PASSED\n\n");
    }
    else
    {
        printf ("\nRANDOM TEST FAILED\n");
        printf("\nREPORT\n");
        printf("shuffle() failed: %d\n",shuffleFails);
        printf("drawCard() failed: %d\n",drawCardFails);
        printf("cardEffect() failed: %d\n",cardEffectFails);
        printf("Treasure Count mismatch: %d\n",treasureCountFails);
        printf("Hand/Deck Count mismatch: %d\n\n",deckHandCountFails);

    }

    //coverage is to be displayed next in the .out so the title is placed here
    printf ("COVERAGE\n");
    return 0;
}

void checkAdventurerEffect(int p, struct gameState *post)
{
    int PostTreasureCount = 0;
    int PreTreasureCount = 0;
    int temphand[MAX_HAND];
    int drawntreasure = 0;

    //inits previous gamestate variable and other game variables
    struct gameState pre;
    int cardDrawn, card;
    int bonus = 0;
    int r,s,t,i;
    int z = 0;

    //copies the previous variable into a post state gamestate variable for comparison
    memcpy(&pre,post,sizeof(struct gameState));

    //calls the adventurerEffect function
    r = cardEffect(adventurer,0,0,0,post,0,&bonus);

    //checks if cardEffect failed
    if(r)
    {
        cardEffectFails++;
    }

    //mocks the adventurerEffect actions
    while(drawntreasure < 2)
    {

        //checks if the deck is empty, if so it shuffles the discard and add to the deck
        if (pre.deckCount[p] < 1)
        {
            s = shuffle(p, &pre);

            //checks if shuffle failed
            if (s == -1 && pre.deckCount[p] >= 1)
            {
                shuffleFails++;
            }
        }

        //draws card
        t = drawCard(p, &pre);

        //checks if drawcard failed
        if (t == -1 && pre.deckCount[p] != 0)
        {
            drawCardFails++;
        }

        //get the most recently drawn card at the top of the hand
        cardDrawn = pre.hand[p][pre.handCount[p] - 1];

        //inc the treasure counter if a treasure is drawn
        if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
        {
            drawntreasure++;
        }

            //otherwise keep drawing and adjust variables to check most recently drawn card
        else
        {
            temphand[z] = cardDrawn;
            pre.handCount[p]--;
            z++;
        }
    }

    //discards all cards that have been drawn
    while(z - 1 >= 0)
    {
        pre.discard[p][pre.discardCount[p]++] = temphand[z - 1];
        z = z - 1;
    }

    //get the post treasure count
    for (i = 0; i < post->handCount[p]; i++)
    {
        card = post->hand[p][i];

        if (card == copper || card == silver || card == gold)
        {
            PostTreasureCount++;
        }
    }

    //gets the pre treasure count
    for (i = 0; i < pre.handCount[p]; i++)
    {
        card = pre.hand[p][i];

        if (card == copper || card == silver || card == gold)
        {
            PreTreasureCount++;
        }
    }

    //checks if the counts are mismatched
    if (PostTreasureCount != PreTreasureCount) {
        treasureCountFails++;
    }

    //gets the values for the hand and deck counts
    int postHC = post->handCount[p];
    int postDC = post->deckCount[p];
    int postDCC = post->discardCount[p];
    int preHC = pre.handCount[p];
    int preDC = pre.deckCount[p];
    int preDCC = pre.discardCount[p];

    //checks if the hand deck counts are mismatched
    if (!(postHC == preHC && postDC == preDC && postDCC == preDCC))
    {
        deckHandCountFails++;
    }
}