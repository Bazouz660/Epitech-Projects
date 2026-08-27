/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** sgt
*/

#include "server.h"
#include "sutils.h"

void sgt(client_t *client, server_t* server, char** args)
{
    char *msg = svaprintf_wish("sgt %.0f", server->clock->freq);

    sendmessage(client, msg);
    free(msg);
}
