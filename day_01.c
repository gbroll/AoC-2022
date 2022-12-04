#include <stdio.h>
#include <stdlib.h>

#define ROW_LEN_MAX 8

__uint32_t solve_day_01(const int numElves)
{
   FILE* inputFile;
    char lineBuf[ROW_LEN_MAX];
    __uint32_t currentElf = 0;
    __uint32_t *topElves = malloc(numElves*sizeof(__uint32_t));
    __uint8_t firstElfToGo = 0;
    __uint32_t heavyElvesSum = 0;

    for (int i = 0; i < numElves; i++)
    {
        topElves[i] = 0;
    }

    inputFile = fopen("input/day_01.txt", "r");
    
    while(fgets(lineBuf, ROW_LEN_MAX, inputFile))
    { 
        if (lineBuf[0] == '\n')
        {
            if (currentElf > topElves[firstElfToGo])
            {
                heavyElvesSum = heavyElvesSum + currentElf - topElves[firstElfToGo];
                topElves[firstElfToGo] = currentElf;
                __uint32_t min = currentElf; 
                for (int i = 0; i < numElves; i++)
                {
                    if (topElves[i] < min)
                    {
                        min = topElves[i];
                        firstElfToGo = i;
                    }
                }
            }
            currentElf = 0;
        }
        else
        {
            currentElf += atoi(lineBuf);
        }
    }

    fclose(inputFile);
    free(topElves);
    return heavyElvesSum;
}

int main(void)
{
    __uint32_t part1 = solve_day_01(1);
    __uint32_t part2 = solve_day_01(3);

    printf("**AoC-2022 day 1 part 1: %d **\n", part1);
    printf("**AoC-2022 day 1 part 2: %d **\n", part2);
}