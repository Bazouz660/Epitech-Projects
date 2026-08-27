/*
** EPITECH PROJECT, 2023
** B-YEP-400-STG-4-1-zappy-basile.trebus-hamann
** File description:
** utils
*/

#include "server.h"

bool can_perform(server_t* server, client_t *cli, float time)
{
    bool can = false;
    session_t *trant = cli->session;
    double elapsed = get_elapsed_time(server);

    if (elapsed > trant->action_timer + (time / server->clock->freq)) {
        trant->action_timer = elapsed;
        can = true;
    }
    if (can == false)
        sendmessage(cli, "ko");
    return can;
}
