#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"

#define MAX_ROW_LEN 64

typedef struct _dir dir;

struct _dir {
    char dirname[MAX_ROW_LEN];
    u64 size;
    dir* parentDir;
    dir* next;
};

dir* makeDir(dir* parentDir, char* dirName)
{
    dir* newDir = (dir*)calloc(1, sizeof(dir));
    newDir->parentDir = parentDir;
    strcpy(newDir->dirname, dirName);
    return newDir;
}

void cdUp(dir** currentDir)
{
    (*currentDir)->parentDir->size += (*currentDir)->size;
    *currentDir = (*currentDir)->parentDir;
    printf("In dir: %s \n", (*currentDir)->dirname);
}

void solve_day_07()
{
    FILE* inputFile;
    char lineBuf[MAX_ROW_LEN];
    
    const char* cd = {"$ cd "};
    const char* ls = {"$ ls"};
    const char* dirString = {"dir "};

    inputFile = fopen("input/day_07.txt", "r");

    fgets(lineBuf, MAX_ROW_LEN, inputFile);
    dir* root = makeDir(NULL, "root");
    dir* currentDir = root;
    
    dir* dirs = root;

    u64 res = 0;
    while (fgets(lineBuf, MAX_ROW_LEN, inputFile))
    {
       // printf("%s", lineBuf);
        if (strncmp(cd, lineBuf, strlen(cd)) == 0)
        {
            if (lineBuf[5] == '.')
            {
                res = (currentDir->size < 1e5)? (res + currentDir->size) : res;
                cdUp(&currentDir);
            }
            else
            {
                dir* newDir = makeDir(currentDir, &lineBuf[5]);
                dirs->next = newDir;
                dirs = newDir;
                currentDir = newDir;
                printf("In dir: %s \n", currentDir->dirname);
            }
        }
        else if (lineBuf[0] >= 48 && lineBuf[0] <= 57)
        {
            currentDir->size += strtol(strtok(lineBuf," "), NULL, 10);
        }
    }

    //return to root
    while(currentDir != root)
    {
        res = (currentDir->size < 1e5) ? (res + currentDir->size) : res;
        cdUp(&currentDir);
    }
    printf("%ld\n", res);
    printf("%ld\n", root->size);

    // Part 2
    u64 reqDeleteSpace = root->size - 4e7;
    u64 res2 = root->size;
    dirs = root;
    while(dirs != NULL)
    {
        if (dirs->size >= reqDeleteSpace && dirs->size <= res2)
        {
            res2 = dirs->size;
        }
        dirs = dirs->next;
    }
    printf("%ld\n", reqDeleteSpace);
    printf("%ld\n", res2);
}


int main(void)
{
    solve_day_07();
}