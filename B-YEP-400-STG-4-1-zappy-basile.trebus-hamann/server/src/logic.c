/*
** EPITECH PROJECT, 2023
** B-YEP-400-STG-4-1-zappy-basile.trebus-hamann
** File description:
** logic
*/

#include "server.h"
#include "commands.h"
#include "sutils.h"

void update_trantorian(server_t *srv, client_t *client)
{
    session_t *trant = client->session;
    int hp = trant->hp;
    int food = trant->inventory->food;

    if (get_elapsed_time(srv) > trant->food_timer + (srv->clock->tu * 126)) {
        trant->food_timer = get_elapsed_time(srv);
        if (food > 0) {
            trant->inventory->food--;
            trant->hp < trant->hp_max ? trant->hp++ : 0;
        } else {
            trant->hp--;
        }
    }
    if (trant->hp <= 0) {
        trant->should_disconnect = true;
        char *arg = itoa(trant->num);
        pdi(client, srv, (char*[]){arg, NULL});
        free(arg);
    }
}

void check_deaths(server_t *server)
{
    ll_node *tmp = server->clients;

    while (tmp) {
        client_t *client = (client_t *)tmp->data;
        if (client->authentified
            && strcmp(client->session->team, "GRAPHIC") != 0
            && client->session->should_disconnect) {
            disconnect_client(server, client);
            tmp = server->clients;
            continue;
        }
        tmp = tmp->next;
    }
}

void update_ai_logic(server_t *server, client_t *client)
{
    if (ll_is_empty(client->command_list))
        return;

    char* command = ll_front(client->command_list)->data;

    if (!check_command(client, command))
        return;
    if (command) {
        char** args = split_string(command, " ", false);
        int status = dispatchcmd_ai(client, server, args);
        if (status == -1 || status == 1) {
            ll_pop_front(&client->command_list);
            free(command);
        }
        free_arr(args);
    }
}

void update_players(server_t *server)
{
    ll_node *tmp = server->clients;

    while (tmp) {
        client_t *client = (client_t *)tmp->data;
        if (client->authentified
            && strcmp(client->session->team, "GRAPHIC") != 0) {
            update_ai_logic(server, client);
            update_trantorian(server, client);
        }
        tmp = tmp->next;
    }
    check_deaths(server);
}

void update_logic(server_t *server)
{
    double et = get_elapsed_time(server);

    if (et > server->map->timeBuffer + server->clock->tu * 20) {
        server->map->timeBuffer = et;
        refill_resources(server, server->map);
    }
    update_players(server);
}
