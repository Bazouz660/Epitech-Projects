/*
** EPITECH PROJECT, 2023
** B-YEP-400-STG-4-1-zappy-basile.trebus-hamann
** File description:
** pgt
*/

#include "server.h"
#include "sutils.h"

void pgt(client_t *client, server_t* server, char** args)
{
    char *msg = svaprintf_wish("pgt %s %s", args[0], args[1]);
    sendmessage(client, msg);
    free(msg);
}
