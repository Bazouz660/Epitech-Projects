/*
** EPITECH PROJECT, 2023
** ZappyPerso
** File description:
** pdi
*/

#include "server.h"
#include "sutils.h"

void pdi(client_t *client, server_t* server, char** args)
{
    session_t *sess = get_session_by_num(server, atoi(args[0]));
    char *msg = NULL;

    msg = svaprintf_wish("pdi %d", sess->num);
    notify_guis(server, msg);
    free(msg);
}
