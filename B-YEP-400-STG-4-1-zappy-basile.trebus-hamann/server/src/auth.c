/*
** EPITECH PROJECT, 2023
** Visual Studio Live Share (Espace de travail)
** File description:
** auth
*/

#include "server.h"
#include "sutils.h"
#include "commands.h"

static void auth_graphic(server_t* server, client_t* client)
{
    if (team_is_full(server, "GRAPHIC"))
        return;
    client->type = GRAPHIC;
    client->authentified = true;
    client->session->team = strdup("GRAPHIC");
    add_team_cli(server, "GRAPHIC", client);
    dprintf(2, "GRAPHIC CLIENT AUTHENTIFIED\n");
    msz(client, server, NULL);
    mct(client, server, NULL);
    tna(client, server, NULL);
}

static void auth_ai(server_t* server, client_t* client, const char* team)
{
    if (!team_exists(server, team) || team_is_full(server, team))
        return;
    client->type = AI;
    client->authentified = true;
    client->session->team = strdup(team);
    add_team_cli(server, team, client);
    dprintf(2, "AI CLIENT AUTHENTIFIED\n");
    msz(client, server, NULL);
    pnw(client, server, NULL);
}

bool authentify(client_t *client, server_t* server, char* command)
{
    char **wrds = split_string(command, " ", true);
    if (get_arr_len((void *)wrds) != 1) {
        free_arr((void **)wrds);
        return false;
    }

    if (team_exists(server, wrds[0])) {
        team_t* team = get_team(server, wrds[0]);
        char *nb_slots = itoa(server->cli_per_team - team->nbcli);
        sendmessage(client, nb_slots);
        free(nb_slots);
    }

    if (strcmp(wrds[0], "GRAPHIC") == 0)
        auth_graphic(server, client);
    else
        auth_ai(server, client, wrds[0]);

    free_arr((void **)wrds);
}
