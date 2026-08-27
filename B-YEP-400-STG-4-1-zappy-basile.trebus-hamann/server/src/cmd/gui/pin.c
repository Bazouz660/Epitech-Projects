/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** pin
*/

#include "server.h"
#include "sutils.h"

void pin(client_t *client, server_t *server, char **args)
{
    session_t *sess = get_session_by_num(server, atoi(args[0]));
    char *msg = NULL;

    msg = svaprintf_wish("pin %d %d %d %d %d %d %d %d %d %d", sess->num,
        sess->x, sess->y, sess->inventory->food, sess->inventory->linemate,
        sess->inventory->deraumere, sess->inventory->sibur,
        sess->inventory->mendiane, sess->inventory->phiras,
        sess->inventory->thystame);
    notify_guis(server, msg);
    free(msg);
}
