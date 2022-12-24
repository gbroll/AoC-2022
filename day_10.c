#include <stdlib.h>
#include <stdio.h>
#include "common.h"

#define MAX_ROW_LEN 16

void noop(u16 *cycle, s16 *xRegValue, u16 *nextEval, u16 *signalStrength, u8 crtScreen[])
{
    //Part 2
    u64 spritePos = (u64)7 << (38 - *xRegValue); 
    u8 crtRow = *cycle/40;
    u64 crtPos = (u64)1 << (39 - (*cycle - crtRow * 40));
    if (spritePos & crtPos)
    {
        crtScreen[*cycle] = '#';
    }
    else
    {
        crtScreen[*cycle] = '.';
    }

    (*cycle)++; 
    
    // Part 1
    if (*cycle == (*nextEval))
    {
        *signalStrength += (*cycle * *xRegValue);
        *nextEval += 40;
    }
}

void addVal(u16 *cycle, s16 *xRegValue, s8 value, u16 *nextEval, u16 *signalStrength, u8 crtScreen[])
{
    noop(cycle, xRegValue, nextEval, signalStrength, crtScreen);
    noop(cycle, xRegValue, nextEval, signalStrength, crtScreen);
    *xRegValue += value;
}

void solveDay10()
{
    char lineBuf[MAX_ROW_LEN];
    u16 cycle = 0;
    s16 xRegValue = 1;
    u16 signalStrength = 0;
    u16 nextEval = 20;

    u8 crtScreen[240];

    FILE* inputFile = fopen("input/day_10.txt", "r");
    
    while(fgets(lineBuf, MAX_ROW_LEN, inputFile))
    {
        if (lineBuf[0] == 'n')
        {
            noop(&cycle, &xRegValue, &nextEval, &signalStrength, crtScreen);
        }

        else if (lineBuf[0] == 'a')
        {
            s8 value = atoi(&lineBuf[5]);
            addVal(&cycle, &xRegValue, value, &nextEval, &signalStrength, crtScreen);
        }

    }
    
    printf("**AoC-2022 day 10 part 1: %d **\n", signalStrength);
    printf("**AoC-2022 day 10 part 2:");
    for (u8 crtPos = 0; crtPos < sizeof(crtScreen); crtPos++)
    {
        if (crtPos % 40 == 0)
        {
            printf("\n");
        }
        printf("%c", crtScreen[crtPos]);
    }
    printf("\n**\n");
    
}

int main()
{
    solveDay10();
    exit(EXIT_SUCCESS);
}