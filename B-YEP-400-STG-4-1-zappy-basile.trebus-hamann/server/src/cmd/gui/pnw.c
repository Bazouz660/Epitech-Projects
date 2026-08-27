/*
** EPITECH PROJECT, 2023
** B-YEP-400-STG-4-1-zappy-basile.trebus-hamann
** File description:
** pnw
*/

#include "server.h"
#include "sutils.h"

void pnw(client_t *client, server_t* server, char** args)
{
    char *msg = svaprintf_wish("pnw %d %d %d %d %d %s",
        client->session->num, client->session->x, client->session->y,
        client->session->orientation, client->session->level,
        client->session->team);
    printf("New player: with num %d\n", client->session->num);
    notify_guis(server, msg);
    free(msg);
}
