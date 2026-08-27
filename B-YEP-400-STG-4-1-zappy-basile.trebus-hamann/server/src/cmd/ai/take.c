/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** take
*/

#include "server.h"
#include "commands.h"
#include "sutils.h"

static bool take_from_tile_2(inventory_t* inv, tile_t* tile, const char *res)
{
    if (strcmp(res, "sibur") == 0 && tile->sibur > 0) {
        tile->sibur--;
        inv->sibur++;
        return true;
    }
    if (strcmp(res, "mendiane") == 0 && tile->mendiane > 0) {
        tile->mendiane--;
        inv->mendiane++;
        return true;
    }
    if (strcmp(res, "phiras") == 0 && tile->phiras > 0) {
        tile->phiras--;
        inv->phiras++;
        return true;
    }
    if (strcmp(res, "thystame") == 0 && tile->thystame > 0) {
        tile->thystame--;
        inv->thystame++;
        return true;
    }

    return false;
}

void print_tile(tile_t* tile)
{
    printf("tile: food: %d, linemate: %d, deraumere: %d, sibur: %d, mendiane: %d, phiras: %d, thystame: %d\n",
    tile->food, tile->linemate, tile->deraumere, tile->sibur, tile->mendiane, tile->phiras, tile->thystame);
}

static bool take_from_tile(inventory_t* inv, tile_t* tile, const char *res)
{
    if (strcmp(res, "food") == 0 && tile->food > 0) {
        tile->food--;
        inv->food++;
        return true;
    }
    if (strcmp(res, "linemate") == 0 && tile->linemate > 0) {
        tile->linemate--;
        inv->linemate++;
        return true;
    }
    if (strcmp(res, "deraumere") == 0 && tile->deraumere > 0) {
        tile->deraumere--;
        inv->deraumere++;
        return true;
    }
    return take_from_tile_2(inv, tile, res);
}

int take(client_t* cli, server_t* server, char** args)
{
    if (!can_perform(server, cli, 7))
        return false;
    if (take_from_tile(cli->session->inventory,
        &server->map->tiles[cli->session->x][cli->session->y], args[1])) {
        sendmessage(cli, "ok");

        char **bct_args = malloc(sizeof(char *) * 3);
        bct_args[0] = svaprintf_wish("%d", cli->session->y);
        bct_args[1] = svaprintf_wish("%d", cli->session->x);
        bct_args[2] = NULL;
        notify_guis_cmd(server, &bct, bct_args);
        free_arr(bct_args);

        char **pin_args = malloc(sizeof(char *) * 2);
        pin_args[0] = svaprintf_wish("%d", cli->session->num);
        pin_args[1] = NULL;
        notify_guis_cmd(server, &pin, pin_args);
        free_arr(pin_args);
        return true;
    } else {
        sendmessage(cli, "ko");
        return -1;
    }
}
