/*
** EPITECH PROJECT, 2023
** B-YEP-400-STG-4-1-zappy-basile.trebus-hamann
** File description:
** init
*/

#include "server.h"

void add_team_cli(server_t* server, const char* team_name, client_t* client)
{
    team_t* team = get_team(server, team_name);

    if (!team)
        return;

    team->clients[team->nbcli++] = client;
    team->clients[team->nbcli] = NULL;
}

team_t *new_team(server_t *server, const char *name)
{
    team_t *team = malloc(sizeof(team_t));

    team->name = strdup(name);
    team->nbcli = 0;
    team->clients = malloc(sizeof(client_t *) * (server->cli_per_team + 1));
    team->clients[0] = NULL;
    return team;
}

void add_team(server_t* server, const char* team)
{
    int nb_teams = 0;

    if (!server->teams) {
        server->teams = malloc(sizeof(team_t*) * 2);
        server->teams[0] = new_team(server, team);
        server->teams[1] = NULL;
        return;
    }
    for (int i = 0; server->teams[i]; i++) {
        if (strcmp(server->teams[i]->name, team) == 0)
            return;
        nb_teams++;
    }
    server->teams = realloc(server->teams, sizeof(team_t*) * (nb_teams + 2));
    server->teams[nb_teams] = new_team(server, team);
    server->teams[nb_teams + 1] = NULL;
}

void init_teams(server_t* server, optinfo_t* args)
{
    server->teams = NULL;
    for (int i = 0; args->teamNames[i]; i++) {
        if (team_exists(server, args->teamNames[i]))
            continue;
        add_team(server, args->teamNames[i]);
    }
    add_team(server, "GRAPHIC");
}
