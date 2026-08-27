/*
** EPITECH PROJECT, 2023
** B-YEP-400-STG-4-1-zappy-basile.trebus-hamann
** File description:
** team
*/

#include "server.h"

bool team_exists(server_t* server, const char* team)
{
    if (!server->teams)
        return false;
    for (int i = 0; server->teams[i]; i++) {
        if (!server->teams[i])
            return false;
        if (strcmp(server->teams[i]->name, team) == 0)
            return true;
    }
    return false;
}

team_t *get_team(server_t *server, const char* team_name)
{
    if (!team_exists(server, team_name))
        return NULL;
    for (int i = 0; server->teams[i]; i++) {
        if (strcmp(server->teams[i]->name, team_name) == 0)
            return server->teams[i];
    }
    return NULL;
}

bool team_is_full(server_t* server, const char* team)
{
    for (int i = 0; server->teams[i]; i++)
        if (strcmp(server->teams[i]->name, team) == 0
            && (server->teams[i]->nbcli >= server->cli_per_team))
            return true;
    return false;
}

void notify_guis(server_t* server, const char *msg)
{
    for (int i = 0; server->teams[i]; i++) {
        for (int j = 0; server->teams[i]->clients[j]; j++) {
            server->teams[i]->clients[j]->type == GRAPHIC ?
                sendmessage(server->teams[i]->clients[j], msg) : 0;
        }
    }
}

void notify_guis_cmd(server_t *server,
    void (*cmd)(client_t *, server_t *, char **), char **args)
{
    for (int i = 0; server->teams[i]; i++) {
        for (int j = 0; server->teams[i]->clients[j]; j++) {
            server->teams[i]->clients[j]->type == GRAPHIC ?
                cmd(server->teams[i]->clients[j], server, args) : 0;
        }
    }
}
