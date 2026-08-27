/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** tna
*/

#include "server.h"
#include "sutils.h"

void tna(client_t *client, server_t* server, char** args)
{
    char *msg = NULL;

    for (int i = 0; server->teams[i] != NULL; i++) {
        if (strcmp(server->teams[i]->name, "GRAPHIC") == 0)
            continue;
        msg = svaprintf_wish("tna %s", server->teams[i]->name);
        sendmessage(client, msg);
        free(msg);
    }
}
