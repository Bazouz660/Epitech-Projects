/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** plv
*/

#include "server.h"
#include "sutils.h"

void plv(client_t *client, server_t* server, char** args)
{
    session_t *sess = get_session_by_num(server, atoi(args[0]));
    char *msg = NULL;

    msg = svaprintf_wish("plv %d %d", sess->num, sess->level);
    notify_guis(server, msg);
    free(msg);
}
