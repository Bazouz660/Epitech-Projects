/*
** EPITECH PROJECT, 2023
** B-YEP-400-STG-4-1-zappy-basile.trebus-hamann
** File description:
** sbp
*/

#include "server.h"
#include "sutils.h"

void sbp(client_t *client, server_t* server, char** args)
{
    char *msg = svaprintf_wish("sbp");
    sendmessage(client, msg);
    free(msg);
}
