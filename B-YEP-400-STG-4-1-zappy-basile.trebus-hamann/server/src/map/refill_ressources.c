/*
** EPITECH PROJECT, 2023
** ZappyPerso
** File description:
** refill_ressources
*/

#include "server.h"
#include "commands.h"
#include "sutils.h"

void add_resource(server_t *srv, enum resource res, int x, int y)
{
    if (res == FOOD)
        srv->map->tiles[x][y].food++;
    if (res == LINEMATE)
        srv->map->tiles[x][y].linemate++;
    if (res == DERAUMERE)
        srv->map->tiles[x][y].deraumere++;
    if (res == SIBUR)
        srv->map->tiles[x][y].sibur++;
    if (res == MENDIANE)
        srv->map->tiles[x][y].mendiane++;
    if (res == PHIRAS)
        srv->map->tiles[x][y].phiras++;
    if (res == THYSTAME)
        srv->map->tiles[x][y].thystame++;

    char **bct_args = malloc(sizeof(char *) * 3);
    bct_args[0] = itoa(x);
    bct_args[1] = itoa(y);
    bct_args[2] = NULL;
    notify_guis_cmd(srv, &bct, bct_args);
    free_arr(bct_args);
}

void add_rand_resources(server_t *server, enum resource res,
    int nbRes, int resMax)
{
    int resToAdd = resMax - nbRes;
    int xRand;
    int yRand;

    for (int i = 0; i < resToAdd; i++) {
        xRand = rand() % server->map->width;
        yRand = rand() % server->map->height;
        add_resource(server, res, xRand, yRand);
    }

}

void print_resources(map_t *map)
{
    printf("food: %d\n", map->food);
    printf("linemate: %d\n", map->linemate);
    printf("deraumere: %d\n", map->deraumere);
    printf("sibur: %d\n", map->sibur);
    printf("mendiane: %d\n", map->mendiane);
    printf("phiras: %d\n", map->phiras);
    printf("thystame: %d\n", map->thystame);
}

void refill_resources(server_t *srv, map_t *map)
{
    add_rand_resources(srv, FOOD, map->food, map->foodMax);
    map->food = map->foodMax;
    add_rand_resources(srv, LINEMATE, map->linemate, map->linemateMax);
    map->linemate = map->linemateMax;
    add_rand_resources(srv, DERAUMERE, map->deraumere, map->deraumereMax);
    map->deraumere = map->deraumereMax;
    add_rand_resources(srv, SIBUR, map->sibur, map->siburMax);
    map->sibur = map->siburMax;
    add_rand_resources(srv, MENDIANE, map->mendiane, map->mendianeMax);
    map->mendiane = map->mendianeMax;
    add_rand_resources(srv, PHIRAS, map->phiras, map->phirasMax);
    map->phiras = map->phirasMax;
    add_rand_resources(srv, THYSTAME, map->thystame, map->thystameMax);
    map->thystame = map->thystameMax;
}
