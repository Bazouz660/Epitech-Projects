/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** msz
*/

#include "server.h"
#include "sutils.h"

void msz(client_t *client, server_t* server, char** args)
{
    char *msg = NULL;

    msg = svaprintf_wish("msz %d %d", server->map->width, server->map->height);
    sendmessage(client, msg);
    free(msg);
}
