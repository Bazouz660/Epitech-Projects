/*
** EPITECH PROJECT, 2023
** B-YEP-400-STG-4-1-zappy-basile.trebus-hamann
** File description:
** edi
*/

#include "server.h"
#include "sutils.h"

void edi(client_t *client, server_t* server, char** args)
{
    char *msg = svaprintf_wish("edi %s", args[0]);
    sendmessage(client, msg);
    free(msg);
}
