/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** pbc
*/

//pbc n M\n

#include "server.h"
#include "sutils.h"

void pbc(client_t *client, server_t* server, char** args)
{
    session_t *sess = get_session_by_num(server, atoi(args[0]));
    char *msg = NULL;

    msg = svaprintf_wish("pbc %d %s", sess->num, args[1]);
    notify_guis(server, msg);
    free(msg);
}
