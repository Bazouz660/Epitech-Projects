/*
** EPITECH PROJECT, 2021
** Dante
** File description:
** find_distances.c
*/

#include "../include/solver.h"

int find_distance_exit(vector2 map_size, int i, int j)
{
    int distance = 0;
    int w = i;
    int k = j;
    vector2 exit = {map_size.x - 1, map_size.y - 1};

    for (int x = j; x < exit.x; x++) {
        k++;
        distance += 10;
    }
    for (int x = i; x < exit.y; x++) {
        w++;
        distance += 10;
    }
    return distance;
}

int find_distance_entry(vector2 map_size, int i, int j)
{
    int distance = 0;
    int w = i;
    int k = j;
    vector2 entry = {0, 0};

    for (int x = i; x > entry.y; x--) {
        w++;
        distance += 10;
    }
    for (int x = j; x > entry.x; x--) {
        k++;
        distance += 10;
    }
    return distance;
}
