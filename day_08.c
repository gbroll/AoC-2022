
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"

#define MAX_ROW_LEN 101
#define ARRAY_DIM 99

u8 treeIsVisibleX(u8 heightMap[ARRAY_DIM][ARRAY_DIM], u8 treeHeight, u8 start, u8 end, u8 y)
{
    u8 treeCount = 0;
    for (u8 xx = start; xx < end; xx++)
    {
        treeCount++;
        if (heightMap[xx][y] >= treeHeight)
        {
            return FALSE;
        }
    }
    return treeCount;
}

u8 treeIsVisibleY(u8 heightMap[ARRAY_DIM][ARRAY_DIM], u8 treeHeight, u8 start, u8 end, u8 x)
{
    for (u8 yy = start; yy < end; yy++)
    {
        if (heightMap[x][yy] >= treeHeight)
        {
            return FALSE;
        }
    }
    return TRUE;
}

typedef enum {
    LEFT, 
    RIGHT, 
    UP,
    DOWN
} Direction;

typedef struct _coord {
    u8 x;
    u8 y;
} Coord; 

u8 move(Coord *pos, Direction dir)
{
    switch (dir)
    {
    case LEFT:
        if (pos->x > 0)
        {
            pos->x--;
            return 1;
        }
        break;
    case RIGHT:
        if (pos->x < (ARRAY_DIM - 1))
        {
            pos->x++;
            return 1;
        }
        break;
    case UP:
        if (pos->y > 0)
        {
            pos->y--;
            return 1;
        }
        break;
    case DOWN:
        if (pos->y < (ARRAY_DIM - 1))
        {
            pos->y++;
            return 1;
        }
        break;
    default:
        break;
    }
    return 0;
}



void solve_day_08()
{
    FILE* inputFile;
    inputFile = fopen("input/day_08.txt", "r");
    char ch;
    u8 x=0, y=0;
    u8 heightMap[ARRAY_DIM][ARRAY_DIM];
    u16 counter = 0;
    
    while ((ch = fgetc(inputFile)) != EOF)
    {
        counter++;
        //printf("%c", ch);
        if (ch == '\n')
        {
            y++;
            x = 0;
        }
        else if (ch != '\0')
        {
            heightMap[x][y] = ch - '0';
            x++;
        }
    }
    fclose(inputFile);

    u16 numTreesVisibleFromOutside = 0;
    u32 maxScenicScore = 0;
    for (x = 0; x < ARRAY_DIM; x++)
    {
        for (y = 0; y < ARRAY_DIM; y++)
        {
            u8 treeHeight = heightMap[x][y];
            u8 treeIsNotVisible = FALSE;
            u32 scenicScore = 1;

            for (u8 dir = LEFT; dir <= DOWN; dir++)
            {
                Coord pos = {.x = x, .y = y};
                u8 numTreesVisibleFomTree = 0;
                while(move(&pos, dir))
                {
                    numTreesVisibleFomTree++;
                    if (heightMap[pos.x][pos.y] >= treeHeight)
                    {
                        treeIsNotVisible |= 1 << dir;
                        break;
                    }
                }
                scenicScore *= numTreesVisibleFomTree;
            }

            if (~treeIsNotVisible & 0xF)
            {
                numTreesVisibleFromOutside++;
            }
            if (scenicScore > maxScenicScore)
            {
                maxScenicScore = scenicScore;
            }
        }
    }
   
   printf("%d\n", numTreesVisibleFromOutside); 
   printf("%d\n", maxScenicScore); 

}

int main()
{
    solve_day_08();
}