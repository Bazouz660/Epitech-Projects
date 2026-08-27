/*
** EPITECH PROJECT, 2023
** B-YEP-400-STG-4-1-zappy-basile.trebus-hamann
** File description:
** smg
*/

#include "server.h"
#include "sutils.h"

void smg(client_t *client, server_t* server, char** args)
{
    char *msg = NULL;

    msg = svaprintf_wish("smg %s", args[0]);
    notify_guis(server, msg);
    free(msg);
}
