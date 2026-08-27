/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** sst
*/

#include "server.h"
#include "commands.h"
#include "sutils.h"

void sst(client_t *client, server_t* server, char** args)
{
    char *msg = NULL;

    if (get_arr_len(args) != 2) {
        sbp(client, server, NULL);
        return;
    }

    server->clock->freq = atoi(args[1]);
    server->clock->tu = (1.0 / server->clock->freq);
    msg = svaprintf_wish("sgt %.0f", server->clock->freq);
    sendmessage(client, msg);
    free(msg);
}
