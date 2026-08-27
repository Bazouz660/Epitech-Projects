/*
** EPITECH PROJECT, 2023
** B-YEP-400-STG-4-1-zappy-basile.trebus-hamann
** File description:
** broadcast
*/

#include "server.h"
#include "sutils.h"

void broadcast(client_t *client, server_t* server, char** args)
{
    ll_node *tmp = server->clients;
    char* str = svaprintf_wish("message %d %d, %s", client->session->x,
            client->session->y, args[1]);
    for (; tmp; tmp = tmp->next) {
        client_t* client_tmp = (client_t*)tmp->data;
        sendmessage(client_tmp, str);
    }
    free(str);
}
