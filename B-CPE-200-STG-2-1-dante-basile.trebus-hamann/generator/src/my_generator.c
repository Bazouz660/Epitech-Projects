/*
** EPITECH PROJECT, 2021
** delivery
** File description:
** my_generator.c
*/

#include "../include/generator.h"
#include "math.h"
#include <time.h>

void display_Maze(generator_t *core, int x, int y)
{
    core->Maze[y - 1][x - 2] = '*';
    for (int i = 0; core->Maze[i] != NULL; i++) {
        write(1, core->Maze[i], x + 1);
    }
}

int top(generator_t *core, int x)
{
    if (core->y != 0 && core->Maze[core->y - 1][core->x] != '*') {
        if (core->x != 0 && core->Maze[core->y][core->x + 1] != '\n' &&
        core->Maze[core->y - 1][core->x - 1] == 'X' && core->Maze[core->y - 1]
        [core->x + 1] == 'X') {
            core->Maze[core->y][core->x] = '*';
            core->Maze[core->y - 1][core->x] = '*';
            core->y = core->y - 1;
            core->pos[core->realx] = core->x;
            core->pos[core->realy] = core->y;
            core->realx = core->realx + 2;
            core->realy = core->realy + 2;
            return (0);
        }
        if (core->x == 0 && core->Maze[core->y][core->x + 1] != '\n' &&
        core->Maze[core->y - 1][core->x + 1] == 'X') {
            core->Maze[core->y][core->x] = '*';
            core->Maze[core->y - 1][core->x] = '*';
            core->y = core->y - 1;
            core->pos[core->realx] = core->x;
            core->pos[core->realy] = core->y;
            core->realx = core->realx + 2;
            core->realy = core->realy + 2;
            return (0);
        }
        if (core->x != 0 && core->Maze[core->y][core->x + 1] == '\n' &&
        core->Maze[core->y - 1][core->x - 1] == 'X') {
            core->Maze[core->y][core->x] = '*';
            core->Maze[core->y - 1][core->x] = '*';
            core->y = core->y - 1;
            core->pos[core->realx] = core->x;
            core->pos[core->realy] = core->y;
            core->realx = core->realx + 2;
            core->realy = core->realy + 2;
            return (0);
        }
    }
    core->count4 = 1;
    return (1);
}

int left(generator_t *core, int x, int y)
{
    if (core->x != 0 && core->Maze[core->y][core->x - 1] != '*') {
        if (core->y != 0 && core->y != y - 1 && core->Maze[core->y - 1]
        [core->x - 1] == 'X' && core->Maze[core->y + 1][core->x - 1] == 'X') {
            core->Maze[core->y][core->x - 1] = '*';
            core->Maze[core->y][core->x] = '*';
            core->x = core->x - 1;
            core->pos[core->realx] = core->x;
            core->pos[core->realy] = core->y;
            core->realx = core->realx + 2;
            core->realy = core->realy + 2;
            return (0);
        }
        if (core->y == 0 && core->y != y - 1 && core->Maze[core->y + 1]
        [core->x - 1] == 'X') {
            core->Maze[core->y][core->x - 1] = '*';
            core->Maze[core->y][core->x] = '*';
            core->x = core->x - 1;
            core->pos[core->realx] = core->x;
            core->pos[core->realy] = core->y;
            core->realx = core->realx + 2;
            core->realy = core->realy + 2;
            return (0);
        }
        if (core->y != 0 && core->y == y - 1 && core->Maze[core->y - 1]
        [core->x - 1] == 'X') {
            core->Maze[core->y][core->x - 1] = '*';
            core->Maze[core->y][core->x] = '*';
            core->x = core->x - 1;
            core->pos[core->realx] = core->x;
            core->pos[core->realy] = core->y;
            core->realx = core->realx + 2;
            core->realy = core->realy + 2;
            return (0);
        }
    }
    core->count1 = 1;
    return (1);
}

int bottom(generator_t *core, int x, int y)
{
    if (core->y != y - 1 && core->Maze[core->y + 1][core->x] != '*') {
        if (core->x != 0 && core->Maze[core->y][core->x + 1] != '\n' &&
        core->Maze[core->y + 1][core->x + 1] == 'X' && core->Maze[core->y + 1]
        [core->x - 1] == 'X') {
            core->Maze[core->y][core->x] = '*';
            core->Maze[core->y + 1][core->x] = '*';
            core->y = core->y + 1;
            core->pos[core->realx] = core->x;
            core->pos[core->realy] = core->y;
            core->realx = core->realx + 2;
            core->realy = core->realy + 2;
            return (0);
        }
        if (core->x == 0 && core->Maze[core->y][core->x + 1] != '\n' &&
        core->Maze[core->y + 1][core->x + 1] == 'X') {
            core->Maze[core->y][core->x] = '*';
            core->Maze[core->y + 1][core->x] = '*';
            core->y = core->y + 1;
            core->pos[core->realx] = core->x;
            core->pos[core->realy] = core->y;
            core->realx = core->realx + 2;
            core->realy = core->realy + 2;
            return (0);
        }
        if (core->x != 0 && core->Maze[core->y][core->x + 1] == '\n' &&
        core->Maze[core->y + 1][core->x - 1] == 'X') {
            core->Maze[core->y][core->x] = '*';
            core->Maze[core->y + 1][core->x] = '*';
            core->y = core->y + 1;
            core->pos[core->realx] = core->x;
            core->pos[core->realy] = core->y;
            core->realx = core->realx + 2;
            core->realy = core->realy + 2;
            return (0);
        }
    }
    core->count3 = 1;
    return (1);
}

int right(generator_t *core, int x, int y)
{
    if (core->Maze[core->y][core->x] != '\n' && core->Maze[core->y][core->x + 1]
    != '\n' && core->Maze[core->y][core->x + 1] != '*') {
        if (core->y != 0 && core->y != y - 1 && core->Maze[core->y + 1]
        [core->x + 1] == 'X' && core->Maze[core->y - 1][core->x + 1] == 'X') {
            core->Maze[core->y][core->x] = '*';
            core->Maze[core->y][core->x + 1] = '*';
            core->x = core->x + 1;
            core->pos[core->realx] = core->x;
            core->pos[core->realy] = core->y;
            core->realx = core->realx + 2;
            core->realy = core->realy + 2;
            return (0);
        }
        if (core->y == 0 && core->y != y - 1 && core->Maze[core->y + 1]
        [core->x + 1] == 'X') {
            core->Maze[core->y][core->x] = '*';
            core->Maze[core->y][core->x + 1] = '*';
            core->x = core->x + 1;
            core->pos[core->realx] = core->x;
            core->pos[core->realy] = core->y;
            core->realx = core->realx + 2;
            core->realy = core->realy + 2;
            return (0);
        }
        if (core->x != 0 && core->y != 0 && core->y == y - 1 && core->Maze
        [core->y - 1][core->x + 1] == 'X') {
            core->Maze[core->y][core->x] = '*';
            core->Maze[core->y][core->x + 1] = '*';
            core->x = core->x + 1;
            core->pos[core->realx] = core->x;
            core->pos[core->realy] = core->y;
            core->realx = core->realx + 2;
            core->realy = core->realy + 2;
            return (0);
        }
    }
    core->count2 = 1;
    return (1);
}


void my_Maze2(generator_t *core, int count, int x, int y)
{
    if (count == 3) {
        left(core, x, y);
    }
    if (count == 4) {
        top(core, x);
    }
    if (core->count1 == 1 && core->count2 == 1 && core->count3 == 1 &&
    core->count3 == 1 && core->count4 == 1) {
        core->count1 = 0;
        core->count2 = 0;
        core->count3 = 0;
        core->count4 = 0;
        if (core->realx <= 0 && core->realy <= 1) {
            display_Maze(core, x, y);
            exit(0);
        }
        core->realx = core->realx - 2;
        core->realy = core->realy - 2;
        core->x = core->pos[core->realx];
        core->y = core->pos[core->realy];
    }
}

void my_Maze(generator_t *core, int x, int y)
{
    core->y = 0;
    core->x = 0;
    int count = 0;
    while (1) {
        count = (rand() % 4) + 1;
        if (count == 1) {
            right(core, x, y);
        }
        if (count == 2) {
            bottom(core, x, y);
        }
        my_Maze2(core, count, x, y);
    }
}

void init_Maze2(generator_t *core, int x, int y)
{
    srand(time(NULL));
    core->Maze = malloc(sizeof(char *) * y);
    for (int i = 0; i < y; i++) {
        core->Maze[i] = malloc(sizeof(char) * (x + 1));
    }
}

void init_Maze(generator_t *core, int x, int y)
{
    int c = 0;
    int i = 0;
    init_Maze2(core, x, y);
    for (; i < y; i++) {
        for (int a = 0; a < x; a++) {
            core->Maze[i][a] = 'X';
            c = a + 1;
        }
        if (i + 1 != y) {
            core->Maze[i][c] = '\n';
        }
    }
    core->Maze[0][0] = '*';
    core->Maze[y - 1][x - 1] = '*';
    if (x == 2 && y == 2) {
        core->Maze[0][1] = '*';
    }
}

void my_generator(int x, int y)
{
    generator_t *core = malloc(sizeof(struct generator_s));
    core->pos = malloc(sizeof(int*) * 1000000);
    for (int i = 0; i < 1000000; i++) {
        core->pos[i] = -1;
    }
    core->realx = 0;
    core->realy = 1;
    init_Maze(core, x, y);
    my_Maze(core, x, y);
    display_Maze(core, x, y);
}
