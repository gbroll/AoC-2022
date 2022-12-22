#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "common.h"

#define MAX_ROW_LEN 8

typedef enum {
    LEFT,
    RIGHT,
    UP, 
    DOWN,
} Direction;

typedef struct _coord coord;

struct _coord {
    s16 x;
    s16 y;
    u32 hash;
    coord* left;
    coord* right;
};

coord* makePoint(s16 x, s16 y)
{
    coord* point = (coord*)malloc(sizeof(coord));
    point->x = x;
    point->y = y;
    point->hash = ((u32)x << 16) + y;

    return point;
}

coord* insert(coord *root, coord *point, u16* numNodes)
{
    if (root == NULL)
    {
        (*numNodes)++;
        return makePoint(point->x, point->y);
    }
    else if (point->hash > root->hash)
    {
        root->right = insert(root->right, point, numNodes);
    }
    else if (point->hash < root->hash)
    {
        root->left = insert(root->left, point, numNodes);
    }
    else
    {
        if (root->x != point->x || root->y != point->y)
        {
            printf("hash collision");
        }
    }
    return root;
}

void cleanup(coord *root)
{
    if (root == NULL)
    {
        return;
    }
    cleanup(root->right);
    cleanup(root->left);
    free(root);
    root = NULL;
}

void move(coord *head, Direction dir)
{
    s8 delta[4][2] = 
    {
        {-1, 0},
        {1, 0}, 
        {0, 1},
        {0, -1}
    };
    head->x += delta[dir][0];
    head->y += delta[dir][1];
    head->hash = ((u32)head->x << 16) + head->y;
}

void follow(coord* head, coord* tail)
{
    s8 delta_x = head->x - tail->x; //-2, -1, 0, 1, 2
    s8 delta_y = head->y - tail->y; //-2, -1, 0, 1, 2
    u8 delta_squared = delta_x * delta_x + delta_y * delta_y;

    if (delta_squared <= 2)
    {

    }
    else if (delta_squared == 4)
    {
        tail->x += delta_x/2;
        tail->y += delta_y/2;
    }
    else if (delta_squared >= 5)
    {
        tail->x = (delta_x > 0)? (tail->x + 1) : (tail->x - 1);
        tail->y = (delta_y > 0)? (tail->y + 1) : (tail->y - 1);
    }
    else
    {
        printf("Something went wrong");
        exit(EXIT_FAILURE);
    }
    tail->hash = ((u32)tail->x << 16) + tail->y;
}

void solve_day_09()
{
    FILE* inputFile;
    char lineBuf[MAX_ROW_LEN];
    
    coord* part1_points = makePoint(0, 0);
    coord* part2_points = makePoint(0, 0);
    u16 part1_numPositions = 1;
    u16 part2_numPositions = 1;

    coord* knots[10];
    for (int i = 0; i < 10; i++)
    {
        knots[i] = makePoint(0,0);
    }
    coord* head = knots[0];
    coord* part1_tail = knots[1];
    coord* part2_tail = knots[9];

    Direction direction;

    inputFile = fopen("input/day_09.txt", "r");
    while(fgets(lineBuf, MAX_ROW_LEN, inputFile))
    {
 
        switch (lineBuf[0])
        {       
        case 'L':
            direction = LEFT;
            break;
        case 'R':
            direction = RIGHT;
            break;
        case 'U':
            direction = UP;
            break;
        case 'D':
            direction = DOWN;
            break;
        default:
            break;
        }

        u8 numSteps = atoi(&lineBuf[2]);
        for (u8 step = 0; step < numSteps; step++)
        {
            move(head, direction);
            for (int i = 0; i < 9; i++)
            {
                follow(knots[i], knots[i+1]);
            }
            insert(part1_points, part1_tail, &part1_numPositions);
            insert(part2_points, part2_tail, &part2_numPositions);
        }
    }
    
    fclose(inputFile);
    cleanup(part1_points);
    cleanup(part2_points);
    for (int i = 0; i < 10; i++)
    {
        cleanup(knots[i]);
    }

    printf("**AoC-2022 day 9 part 1: %d **\n", part1_numPositions);
    printf("**AoC-2022 day 9 part 2: %d **\n", part2_numPositions);

}


int main()
{   
    clock_t begin = clock();
    solve_day_09();
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("%f\n", time_spent);
}