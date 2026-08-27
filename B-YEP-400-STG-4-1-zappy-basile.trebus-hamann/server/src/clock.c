/*
** EPITECH PROJECT, 2023
** B-YEP-400-STG-4-1-zappy-basile.trebus-hamann
** File description:
** clock
*/

#include "server.h"

void init_clock(server_t* server, optinfo_t* args)
{
    server->clock = malloc(sizeof(zpy_clock_t));
    server->clock->freq = args->freq;
    gettimeofday(&server->clock->start, NULL);
    gettimeofday(&server->clock->end, NULL);
    server->clock->tu = (1.0 / server->clock->freq);
}

double get_elapsed_time(server_t* server)
{
    gettimeofday(&server->clock->end, NULL);
    double elapsed_sec = (double)(server->clock->end.tv_sec \
    - server->clock->start.tv_sec);
    double elapsed_usec = (double)(server->clock->end.tv_usec \
    - server->clock->start.tv_usec) / 1e6;
    return elapsed_sec + elapsed_usec;
}
