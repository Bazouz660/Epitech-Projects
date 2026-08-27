/*
** EPITECH PROJECT, 2021
** Dante
** File description:
** generator.h
*/

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct generator_s {
    char **Maze;
    int *pos;
    int x;
    int y;
    int count1;
    int count2;
    int count3;
    int count4;
    int realx;
    int realy;
} generator_t;

void my_generator(int x, int y);
void init_Maze(generator_t *core, int x, int y);
void init_Maze2(generator_t *core, int x, int y);
void display_Maze(generator_t *core, int x, int y);
void my_Maze(generator_t *core, int x, int y);
void my_Maze2(generator_t *core, int count, int x, int y);
int top(generator_t *core, int x);
int left(generator_t *core, int x, int y);
int bottom(generator_t *core, int x, int y);
int right(generator_t *core, int x, int y);
