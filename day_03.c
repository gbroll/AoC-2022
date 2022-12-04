#include <stdio.h>
#include <string.h>
#include "common.h"

#define MAX_ROW_LEN 64

__uint16_t* solve_day_03(void)
{
    static __uint16_t result[2] = {0, 0};

    FILE* inputFile;
    char lineBuf[MAX_ROW_LEN];
    __uint64_t chars[2];
    __uint64_t group = ~0;
    __uint8_t prio;
    __uint8_t numInGroup = 0;
    
    inputFile = fopen("input/day_03.txt", "r");

    while (fgets(lineBuf, MAX_ROW_LEN, inputFile))
    {
        numInGroup++;
        chars[0] = 0;
        chars[1] = 0;

        for (int i = 0, n = strlen(lineBuf)-1; i < n; i++)
        {
            prio = (lineBuf[i] >= 'a')? (lineBuf[i] - 96) : (lineBuf[i] - 38);
            chars[i/(n/2)] |= (1ULL << prio);
            if ((chars[0] & chars[1]) && !(chars[0] & 1ULL))
            {
                result[0] += prio;
                chars[0] |= 1ULL;
            }
        }
        chars[0] &= ~1ULL;
        group &= (chars[0] |= chars[1]);
        
        if (numInGroup == 3)
        {
            numInGroup = 0;
            for (int i = 1; i < 53; i ++)
            {
                if (group & (1ULL << i))
                {
                    result[1] += i;
                    break;
                }
            }
            group = ~0;
        }
    } 
    fclose(inputFile);
    return &result[0];   
}

int main(void)
{
    __uint16_t* res = solve_day_03();
    printf("**AoC-2022 day 3 part 1: %d **\n", res[PART_ONE]);
    printf("**AoC-2022 day 3 part 2: %d **\n", res[PART_TWO]);

}