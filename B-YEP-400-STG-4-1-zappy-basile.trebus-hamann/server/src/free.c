/*
** EPITECH PROJECT, 2023
** B-YEP-400-STG-4-1-zappy-basile.trebus-hamann
** File description:
** free
*/

#include "server.h"
#include "sutils.h"

void free_args(optinfo_t **args)
{
    optinfo_t *tmp = *args;

    free_arr(tmp->teamNames);
    free(tmp);
}

static void free_map(server_t *server)
{
    for (int i = 0; i < server->map->height; i++)
        free(server->map->tiles[i]);
    free(server->map->tiles);
    free(server->map);
}

void close_server(server_t* server)
{
    fprintf(stderr, "Closing server...\n");

    fprintf(stderr, "Closing clients: %d clients still connected\n",
        ll_size(server->clients));

    while (!ll_is_empty(server->clients))
        disconnect_client(server, ll_back(server->clients)->data);

    for (int i = 0; server->teams[i]; i++) {
        free(server->teams[i]->clients);
        free(server->teams[i]->name);
        free(server->teams[i]);
    }

    free(server->teams);
    free_map(server);
}
