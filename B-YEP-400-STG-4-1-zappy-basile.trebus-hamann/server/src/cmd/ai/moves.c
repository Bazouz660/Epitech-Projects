/*
** EPITECH PROJECT, 2023
** B-YEP-400-STG-4-1-zappy-basile.trebus-hamann
** File description:
** aimoves
*/

#include "server.h"
#include "commands.h"
#include "sutils.h"

void send_pos(client_t* client, server_t* server)
{
    sendmessage(client, "ok");
    char **ppo_args = malloc(sizeof(char *) * 2);
    ppo_args[0] = svaprintf_wish("%d", client->session->num);
    ppo_args[1] = NULL;
    ppo(client, server, ppo_args);
    free_arr(ppo_args);
}

int forward(client_t* client, server_t* server, char** args)
{
    if (!can_perform(server, client, 7))
        return false;
    switch (client->session->orientation) {
        case NORTH:
            client->session->y = client->session->y - 1 < 0
                ? server->map->height - 1 : client->session->y - 1;
            break;
        case EAST:
            client->session->x = client->session->x - 1 < 0
                ? server->map->width - 1 : client->session->x - 1;
            break;
        case SOUTH:
            client->session->y = client->session->y + 1 >= server->map->height
                ? 0 : client->session->y + 1;
            break;
        case WEST:
            client->session->x = client->session->x + 1 >= server->map->width
                ? 0 : client->session->x + 1;
            break;
    }
    send_pos(client, server);
    return true;
}

int right(client_t* client, server_t* server, char** args)
{
    if (!can_perform(server, client, 7))
        return false;
    client->session->orientation = (client->session->orientation - 1) % 4;
    send_pos(client, server);
    return true;
}

int left(client_t* client, server_t* server, char** args)
{
    if (!can_perform(server, client, 7))
        return false;
    client->session->orientation = (client->session->orientation + 1) % 4;
    send_pos(client, server);
    return true;
}
