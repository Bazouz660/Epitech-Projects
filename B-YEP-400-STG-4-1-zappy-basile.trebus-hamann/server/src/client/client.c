/*
** EPITECH PROJECT, 2023
** B-YEP-400-STG-4-1-zappy-basile.trebus-hamann
** File description:
** client
*/

#include "server.h"
#include "commands.h"
#include "sutils.h"

void free_session(client_t* client)
{
    if (client->session) {
        if (client->session->team)
            free(client->session->team);
        free(client->session);
    }
}

void disconnect_client(server_t* server, client_t* client)
{
    char **args = malloc(sizeof(char *) * 2);
    args[0] = svaprintf_wish("%d", client->session->num);
    args[1] = NULL;

    if (client->type == AI)
        pdi(client, server, args);
    if (client->session && client->session->team) {
        team_t *team = get_team(server, client->session->team);
        team->nbcli--;
    }
    free_arr(args);
    close(client->fd_con);
    free_session(client);
    while (!ll_is_empty(client->command_list))
        ll_pop_front(&client->command_list);
    ll_node* tmp = server->clients;
    while (tmp) {
        if (tmp->data == client) {
            ll_pop_node(&server->clients, tmp);
            server->nbcli--;
            break;
        }
        tmp = tmp->next;
    }
    free(client);
}

static client_t* newcli(server_t* server)
{
    client_t *cli;
    cli = malloc(sizeof(client_t));
    cli->addr_len = sizeof(cli->address);
    cli->fd_con = accept(server->fd_con,
        (struct sockaddr*)&cli->address, &cli->addr_len);
    cli->session = newsess();
    cli->session->action_timer = get_elapsed_time(server);
    cli->command_list = NULL;
    cli->authentified = false;
    cli->type = UNKNOWN;
    return cli;
}

void addcli(server_t* server)
{
    if (server->nbcli >= server->maxcli)
        close(accept(server->fd_con, NULL, NULL));
    else {
        server->clients = ll_push_back(server->clients, newcli(server));
        server->nbcli++;
        sendmessage((client_t *)ll_back(server->clients)->data, "WELCOME");
    }
}

session_t *get_session_by_num(server_t *server, int num)
{
    ll_node *tmp = server->clients;
    client_t *cli;

    while (tmp) {
        cli = (client_t *)tmp->data;
        if (cli->session->num == num)
            return cli->session;
        tmp = tmp->next;
    }
    return NULL;
}
