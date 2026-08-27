/*
** EPITECH PROJECT, 2023
** B-YEP-400-STG-4-1-zappy-basile.trebus-hamann
** File description:
** player
*/

#include "server.h"
#include "sutils.h"

void connect_nbr(client_t* client, server_t* server, char** args)
{
    team_t* team = get_team(server, client->session->team);
    char* str = svaprintf_wish("%d", server->maxcli - team->nbcli);
    sendmessage(client, str);
    free(str);
}
