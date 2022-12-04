#include <stdio.h>

#define ROW_LEN_MAX 5

enum {
    PART_ONE,
    PART_TWO
} part;

__uint8_t getIndex(char inp)
{
    if (inp == 'A' || inp == 'X')
    {
        return 0;
    } 
    else if (inp == 'B' || inp == 'Y')
    {
        return 1;
    }
    return 2;
}

__uint8_t getIndexFromRes(__uint8_t inp, char res)
{
    if (res == 'Y')
    {
        return inp;
    }
    else if (res == 'X')
    {
        return (inp > 0)? (inp - 1) : 2;
    }
    return (inp < 2)? (inp + 1) : 0;
}

__uint16_t* solve_day_02()
{
    __uint8_t pointsTable[3][3] = {
        {4, 8, 3},
        {1, 5, 9},
        {7, 2, 6}
    };

    FILE* inputFile;
    char lineBuf[ROW_LEN_MAX];
    char you, me;
    static __uint16_t points[2] = {0, 0};

    inputFile = fopen("input/day_02.txt", "r");
    while(fgets(lineBuf, ROW_LEN_MAX, inputFile))
    {
        you = getIndex(lineBuf[0]);
        me = getIndex(lineBuf[2]);
        points[PART_ONE] += pointsTable[you][me];
        me = getIndexFromRes(you, lineBuf[2]);
        points[PART_TWO] += pointsTable[you][me];
    }
    fclose(inputFile);
    return &points[0];
}

int main(void)
{
    __uint16_t* res = solve_day_02();
    printf("**AoC-2022 day 2 part 1: %d **\n", res[PART_ONE]);
    printf("**AoC-2022 day 2 part 2: %d **\n", res[PART_TWO]);
}