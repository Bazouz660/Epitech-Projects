/*
** EPITECH PROJECT, 2023
** B-YEP-400-STG-4-1-zappy-basile.trebus-hamann
** File description:
** session
*/

#include "server.h"

void init_inventory(session_t *sess)
{
    sess->inventory = malloc(sizeof(inventory_t));
    sess->inventory->food = 0;
    sess->inventory->linemate = 0;
    sess->inventory->deraumere = 0;
    sess->inventory->sibur = 0;
    sess->inventory->mendiane = 0;
    sess->inventory->phiras = 0;
    sess->inventory->thystame = 0;
}

session_t *newsess(void)
{
    static int num = 0;

    session_t *sess = malloc(sizeof(session_t));
    sess->should_disconnect = false;
    sess->x = 0;
    sess->y = 0;
    uuid_generate(sess->uuid);
    sess->num = num++;
    sess->level = 1;
    sess->food_timer = 0;
    sess->action_timer = 0;
    sess->hp = 10;
    sess->hp_max = 10;
    sess->team = NULL;
    sess->orientation = NORTH;
    init_inventory(sess);
    return sess;
}
