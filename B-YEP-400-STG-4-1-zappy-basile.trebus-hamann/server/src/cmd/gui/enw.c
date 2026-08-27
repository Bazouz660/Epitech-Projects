/*
** EPITECH PROJECT, 2023
** B-YEP-400-STG-4-1-zappy-basile.trebus-hamann
** File description:
** enw
*/

#include "server.h"
#include "sutils.h"

void enw(client_t *client, server_t* server, char** args)
{
    char *msg = svaprintf_wish("enw %s %s %s %s", args[0], args[1], args[2], args[3]);
    sendmessage(client, msg);
    free(msg);
}
