/*
** EPITECH PROJECT, 2021
** Dante
** File description:
** solver.h
*/

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

typedef struct solver_grid {
    int g;
    int h;
    int cost;
} solver_grid;

typedef struct vector2 {
    int x;
    int y;
} vector2;

typedef struct path {
    int x;
    int y;
    struct path *next;
    struct path *prev;
} path;

typedef struct solver {
    solver_grid **sg;
    int solved;
    int i;
    int j;
    int first;
    vector2 lastpos;
    vector2 move;
    vector2 start;
    vector2 exit;
    path *p;
} solver;

typedef struct cheapest_s {
    char **map;
    solver s;
    vector2 map_size;
    vector2 move;
    int cost;
    int found;
} cheapest_s;

typedef struct zinzin {
    path *p;
    solver s;
    vector2 move;
    vector2 lastpos;
    vector2 lastlastpos;
} zinzin;

void print_map(char **, vector2);
int find_distance_entry(vector2, int, int);
int find_distance_exit(vector2, int, int);
char **my_str_to_word_array(char *);
char *read_file(char *);
int is_at_crossroad(char **, solver, vector2);
int check_for_blob(char **, vector2, vector2);
char **clean_map(char **, vector2);
void print_map(char **, vector2);
void init_solver(solver *s, vector2 map_size);
void attach_prev_node(solver *s, int *first);
void update_path(char **map, vector2 map_size, solver s);
vector2 reverse_path(char **map, solver s, vector2 map_size);
vector2 find_cheapest_move(char **map, solver s, vector2 map_size);
cheapest_s check_up(cheapest_s cs);
cheapest_s check_down(cheapest_s cs);
cheapest_s check_left(cheapest_s cs);
cheapest_s check_right(cheapest_s cs);
cheapest_s check_up2(cheapest_s cs);
cheapest_s check_down2(cheapest_s cs);
cheapest_s check_left2(cheapest_s cs);
cheapest_s check_right2(cheapest_s cs);
cheapest_s check_up_backtracking(cheapest_s cs);
cheapest_s check_down_backtracking(cheapest_s cs);
cheapest_s check_left_backtracking(cheapest_s cs);
cheapest_s check_right_backtracking(cheapest_s cs);
cheapest_s check_up_backtracking2(cheapest_s cs);
cheapest_s check_down_backtracking2(cheapest_s cs);
cheapest_s check_left_backtracking2(cheapest_s cs);
cheapest_s check_right_backtracking2(cheapest_s cs);
vector2 find_cheapest_move_backtracking(char **, solver, vector2);
void prevnode(solver *s);
