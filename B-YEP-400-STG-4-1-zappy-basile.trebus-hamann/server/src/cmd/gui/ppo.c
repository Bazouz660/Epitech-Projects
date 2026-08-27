/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** ppo
*/

#include "server.h"
#include "sutils.h"

void ppo(client_t *client, server_t *server, char **args)
{
    session_t *sess = get_session_by_num(server, atoi(args[0]));
    char *msg = NULL;

    msg = svaprintf_wish("ppo %d %d %d %d", sess->num,
        sess->x, sess->y, sess->orientation + 1);
    notify_guis(server, msg);
    free(msg);
}
