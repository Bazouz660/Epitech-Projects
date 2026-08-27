/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** bct
*/

#include "server.h"
#include "sutils.h"

void bct(client_t *client, server_t *server, char **args)
{
    char *msg = NULL;
    int y = atoi(args[0]);
    int x = atoi(args[1]);

    msg = svaprintf_wish("bct %d %d %d %d %d %d %d %d %d", x, y,
        server->map->tiles[x][y].food, server->map->tiles[x][y].linemate,
        server->map->tiles[x][y].deraumere, server->map->tiles[x][y].sibur,
        server->map->tiles[x][y].mendiane, server->map->tiles[x][y].phiras,
        server->map->tiles[x][y].thystame);
    sendmessage(client, msg);
    free(msg);
}

void mct(client_t *client, server_t* server, char** args)
{
    char **pos = malloc(sizeof(char*) * 3);

    for (int y = 0; y < server->map->height; y++) {
        for (int x = 0; x < server->map->width; x++) {
            pos[0] = itoa(y);
            pos[1] = itoa(x);
            bct(client, server, pos);
            free(pos[0]);
            free(pos[1]);
        }
    }
    free(pos);
}
