#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"

#define MAX_ROW_LEN 16

typedef struct _range {
    __uint8_t low;
    __uint8_t high;
    __uint8_t length;
} range;

range makeRange(char* strInOut)
{
    range retVal;
    char *ptr;
    ptr = strtok(strInOut, "-");
    retVal.low = atoi(ptr);
    ptr = strtok(NULL, "-");
    retVal.high = atoi(ptr);
    retVal.length = retVal.high - retVal.low;
    return retVal;
}

__uint8_t rangeContainedInRange(range range1, range range2)
{
    __uint8_t low = range1.low < range2.low? range1.low : range2.low;
    __uint8_t high = range1.high > range2.high? range1.high : range2.high;
    __uint8_t length = high-low;
    if (length == range1.length || length == range2.length)
    {
        return 1;
    }
    return 0;
}

__uint8_t rangesOverlap(range range1, range range2)
{
    if (range1.low <= range2.high && range2.low <= range1.high)
    {
        return 1;
    }
    return 0;
}


__uint16_t* solve_day_04()
{
    static __uint16_t result[2] = {0, 0};

    FILE* inputFile;
    char lineBuf[MAX_ROW_LEN];
    char *str1, *str2;

    inputFile = fopen("input/day_04.txt", "r");
    while (fgets(lineBuf, MAX_ROW_LEN, inputFile))
    {
        str1 = strtok(lineBuf, ",");
        str2 = strtok(NULL, ",");
        range elf1Sections = makeRange(str1);
        range elf2Sections = makeRange(str2);
        result[0] += rangeContainedInRange(elf1Sections, elf2Sections);
        result[1] += rangesOverlap(elf1Sections, elf2Sections);
    }

    fclose(inputFile);
    return &result[0];
}

int main(void)
{
    __uint16_t* res = solve_day_04();
    printf("**AoC-2022 day 4 part 1: %d **\n", res[PART_ONE]);
    printf("**AoC-2022 day 4 part 2: %d **\n", res[PART_TWO]);
}
