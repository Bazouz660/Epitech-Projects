/*
** EPITECH PROJECT, 2023
** B-YEP-400-STG-4-1-zappy-basile.trebus-hamann
** File description:
** inv
*/

#include "server.h"
#include "sutils.h"

void inventory(client_t *client, server_t *server, char** args)
{
    inventory_t* inv = client->session->inventory;
    char* str = svaprintf_wish("[food %d, linemate %d, deraumere %d, "
        "sibur %d, mendiane %d, phirasme %d, thystame %d]", inv->food,
        inv->linemate, inv->deraumere, inv->sibur, inv->mendiane, inv->phiras,
        inv->thystame);
    sendmessage(client, str);
    free(str);
}