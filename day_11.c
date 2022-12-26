#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"

#define MAX_ROW_LEN 64
#define MAX_NUM_MONKEYS 10

typedef u64 (*Operation)(u64 worryLevel, const u8 value);

typedef struct _item item;
typedef struct _item {
    u64 worryLevel;
    item* next;
} item;

typedef struct _list {
    item* firstItem;
    item* lastItem;
    u8 length;
} itemList; 

typedef struct _monkey monkey;
struct _monkey {
    item* firstItem;
    item* LastItem;
    itemList items; 
    Operation op;
    u8 operand;
    u8 testDivisor;
    u8 testTrueReciever;
    u8 testFalseReciever;
    u64 numItemsInspected;
};

void itemAppend(itemList* list, item* element)
{
    if (list->length == 0)
    {
        list->firstItem = element;
        list->lastItem = element;
    }
    else
    {
        list->lastItem->next = element;
        list->lastItem = element;
    }
    element->next = NULL;
    (list->length)++;
}

item* itemRemove(itemList* list)
{
    item* it = list->firstItem;

    if (list->length == 1)
    {
        list->firstItem = NULL;
        list->lastItem = NULL;
    }
    else
    {
        list->firstItem = list->firstItem->next;
    }
    (list->length)--;
    return it;
}


u64 opAdd(u64 worryLevel, const u8 value)
{
    return worryLevel + (u64)value;
}

u64 opMultiply(u64 worryLevel, const u8 value)
{
    return worryLevel * (u64)value;
}

u64 opSquare(u64 worryLevel, const u8 value)
{
    return worryLevel * (u64)worryLevel;
}

monkey* parseInput(u8* numMonkeys)
{
    FILE* inputFile = fopen("input/day_11.txt", "r");
    char lineBuf[MAX_ROW_LEN];

    static monkey monkeys[MAX_NUM_MONKEYS];
    s8 monkeyIndex = -1;

    while(fgets(lineBuf, MAX_ROW_LEN, inputFile))
    {
        if (strncmp(lineBuf, "Monkey", 6) == 0)
        {
            monkeyIndex++;
            monkeys[monkeyIndex].firstItem = NULL;

            item* it = NULL;
            item* prevItem = NULL;
            u8 numItems = 0;

            fgets(lineBuf, MAX_ROW_LEN, inputFile);
            char* tok = strtok(&lineBuf[18], ",");
            while (tok != NULL)
            {
                numItems++;
                prevItem = it;
                it = (item*)malloc(sizeof(item));
                it->worryLevel = atoi(tok);
                if (monkeys[monkeyIndex].firstItem == NULL)
                {
                    monkeys[monkeyIndex].firstItem = it;
                } 
                else
                {
                    prevItem->next = it;
                }
                tok = strtok(NULL, ",");
            }
            monkeys[monkeyIndex].LastItem = it;
            monkeys[monkeyIndex].items.firstItem = monkeys[monkeyIndex].firstItem;
            monkeys[monkeyIndex].items.lastItem = it;
            monkeys[monkeyIndex].items.length = numItems;

            fgets(lineBuf, MAX_ROW_LEN, inputFile);
            if (lineBuf[23] == '+')
            {
                monkeys[monkeyIndex].op = opAdd;
                monkeys[monkeyIndex].operand = atoi(&lineBuf[25]);
            }
            else if (lineBuf[23] == '*')
            {
                if (strncmp(&lineBuf[25], "old", 3) == 0)
                {
                    monkeys[monkeyIndex].op = opSquare;
                }
                else
                {
                    monkeys[monkeyIndex].op = opMultiply;
                    monkeys[monkeyIndex].operand = atoi(&lineBuf[25]);
                }
            }

            fgets(lineBuf, MAX_ROW_LEN, inputFile);
            monkeys[monkeyIndex].testDivisor = atoi(&lineBuf[21]);

            fgets(lineBuf, MAX_ROW_LEN, inputFile);
            monkeys[monkeyIndex].testTrueReciever = atoi(&lineBuf[29]);

            fgets(lineBuf, MAX_ROW_LEN, inputFile);
            monkeys[monkeyIndex].testFalseReciever = atoi(&lineBuf[29]);
        }
    }
    fclose(inputFile);
    *numMonkeys = monkeyIndex + 1;
    return &monkeys[0];
}

void solveDay11()
{
    u8 numMonkeys;
    monkey* monkeys = parseInput(&numMonkeys);
    const u16 numRounds = 10000;

    //part2
    u64 testDivisorProduct = 1;
    for (u8 monkeyNum = 0; monkeyNum < numMonkeys; monkeyNum++)
    {
        testDivisorProduct *= monkeys[monkeyNum].testDivisor;
    }


    for (u16 round = 0; round < numRounds; round++)
    {
        for (u8 monkeyNum = 0; monkeyNum < numMonkeys; monkeyNum++)
        {

            while (monkeys[monkeyNum].items.length > 0)
            {
                monkeys[monkeyNum].numItemsInspected++;
                item* it = itemRemove(&monkeys[monkeyNum].items);
                //it->worryLevel = monkeys[monkeyNum].op(it->worryLevel, monkeys[monkeyNum].operand)/3;  
                it->worryLevel = (monkeys[monkeyNum].op(it->worryLevel, monkeys[monkeyNum].operand)) % testDivisorProduct;

                u8 reciever;
                if (it->worryLevel % monkeys[monkeyNum].testDivisor)
                {
                    reciever = monkeys[monkeyNum].testFalseReciever;
                }
                else
                {
                    reciever = monkeys[monkeyNum].testTrueReciever;
                }

                itemAppend(&monkeys[reciever].items, it);
            }
        }
    }
    
    u64 a = 0, b = 0;
    for (u8 monkeyNum = 0; monkeyNum < numMonkeys; monkeyNum++)
    {
        if (monkeys[monkeyNum].numItemsInspected > a)
        {
            if (a < b)
            {
                a = monkeys[monkeyNum].numItemsInspected;
            }
            else
            {
                b =  monkeys[monkeyNum].numItemsInspected;
            }
        }
    }

    printf("%ld\n", a*b);
}

int main()
{
    solveDay11();
    exit(EXIT_SUCCESS);
}