#include <stdio.h>
#include <stdlib.h>
#include "common.h"

typedef struct _cbuf {
    u8 size;
    u8 index;
    u32* values;
} cbuf;

cbuf makeCircularBuf(u8 size)
{
    cbuf buf = {.size = size, .index = size-1, .values = NULL};
    buf.values = (u32*)malloc(buf.size*sizeof(u32));
    return buf;
}

void cbufPush(cbuf* buf, u32 value)
{
    buf->index = (buf->index == (buf->size - 1))? 0 : buf->index+1;
    buf->values[buf->index] = value;
}

u8 allElementsAreUnique(cbuf* buf)
{
    u32 res = buf->values[0];
    for (u8 i = 1; i < buf->size; i++)
    {
        if (res & buf->values[i])
        {
            return FALSE;
        }
        res |= buf->values[i];
    }
    return TRUE;
}

void solve_day_06(__uint16_t* results)
{
    FILE* inputFile;
    inputFile = fopen("input/day_06.txt", "r");

    cbuf buf[2] = {makeCircularBuf(4), makeCircularBuf(14)};

    char ch;
    u16 count = 0;
    while((ch = fgetc(inputFile)))
    {
        if (results[PART_ONE] & results[PART_TWO])
        {
            break;
        }
        count++;

        for (Part part = PART_ONE; part <= PART_TWO; part++)
        {
            if (results[part])
            {
                continue;
            }
            cbufPush(&buf[part], (u32)1 << (ch-'a'));
            if (count >= buf[part].size && allElementsAreUnique(&buf[part]))
            {
                results[part] = count;
                free(buf[part].values);
            }
        }
    }

    fclose(inputFile);
}

int main(void)
{
    u16 res[2] = {0, 0};
    solve_day_06(&res[0]);

    printf("**AoC-2022 day 6 part 1: %d **\n", res[PART_ONE]);
    printf("**AoC-2022 day 6 part 2: %d **\n", res[PART_TWO]);
}