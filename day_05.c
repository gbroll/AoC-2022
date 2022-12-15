#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROW_LEN 40
#define MAX_STACK_HEIGHT 100

typedef struct _stack {
    __uint8_t height;
    char arr[MAX_STACK_HEIGHT];
} stack;

stack make_stack()
{
    stack st = {.height = 0, .arr = {0}};
    return st; 
}

void stack_push(stack *st, char value[], __uint8_t len)
{
    if ((st->height + len) <= MAX_STACK_HEIGHT)
    { 
        for (int i = 0; i < len; i++)
        {
            st->arr[st->height + i] = value[i];
        }
        st->height += len;
        return;
    }
    exit(EXIT_FAILURE);
}

void stack_pop(stack *st, char value[], __uint8_t len)
{
    if ((st->height - len ) >= 0)
    {
        for (int i = 0; i < len; i++)
        {
            value[i] = st->arr[st->height - len  + i];
        }
        st->height -= len;
        return;
    }
    exit(EXIT_FAILURE);
}


int solve_day_05()
{
    FILE* inputFile;
    char lineBuf[MAX_ROW_LEN];
    
    const __uint8_t numStacks = 9;
    stack* stacks = (stack*)malloc(numStacks * sizeof(stack));
    for (__uint8_t i = 0; i < numStacks; i++)
    {
        stacks[i] = make_stack();
    }

    inputFile = fopen("input/day_05.txt", "r");
    
    /* Init stacks */
    for (__uint16_t lineNum = 0; lineNum < 8; lineNum++) 
    {
        fgets(lineBuf, MAX_ROW_LEN, inputFile);
        printf("%s", lineBuf);
        for (__uint8_t i = 0; i < numStacks; i++)
        {
            char crate = lineBuf[1+i*4];
            if (crate != ' ')
            {
                stacks[i].arr[7-lineNum] = crate;
                stacks[i].height = (8-lineNum) > stacks[i].height ? (8-lineNum) : stacks[i].height;
            }
        }       
    }
    stack* stacks_set2 = (stack*)malloc(numStacks * sizeof(stack));
    memcpy(stacks_set2, stacks, numStacks*sizeof(stack));

    /* Discard lines*/
    fgets(lineBuf, MAX_ROW_LEN, inputFile);
    fgets(lineBuf, MAX_ROW_LEN, inputFile);

    while (fgets(lineBuf, MAX_ROW_LEN, inputFile))
    {
        __uint8_t numCrates, from, to;
             
        atoi(strtok(lineBuf, " "));
        numCrates = atoi(strtok(NULL, " "));
        atoi(strtok(NULL, " "));
        from = atoi(strtok(NULL, " "));
        atoi(strtok(NULL, " "));
        to = atoi(strtok(NULL, " "));

        /* Part 1 */
        char crate[1];
        for (__uint8_t i = 0; i < numCrates; i++)
        {
            stack_pop(&stacks[from - 1], crate, 1);
            stack_push(&stacks[to - 1], crate, 1);
        } 

        /* Part 2 */
        char* crates = (char*)malloc(numCrates*sizeof(char));
        stack_pop(&stacks_set2[from - 1], crates, numCrates);
        stack_push(&stacks_set2[to - 1], crates, numCrates);
        free(crates); 
    }
    
    for (int i = 0; i < numStacks; i++)
    {
        printf("%c", stacks[i].arr[stacks[i].height - 1]);
    }
    printf("\n");
    for (int i = 0; i < numStacks; i++)
    {
        printf("%c", stacks_set2[i].arr[stacks[i].height - 1]);
    }

    free(stacks);
    free(stacks_set2);
}

int main(void)
{
    solve_day_05();
}