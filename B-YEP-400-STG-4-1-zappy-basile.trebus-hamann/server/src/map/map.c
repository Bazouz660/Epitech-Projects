/*
** EPITECH PROJECT, 2023
** B-YEP-400-STG-4-1-zappy-basile.trebus-hamann
** File description:
** map
*/

#include "server.h"

void init_tile(map_t* map, int x, int y)
{
    map->tiles[x][y].food = 0;
    map->tiles[x][y].linemate = 0;
    map->tiles[x][y].deraumere = 0;
    map->tiles[x][y].sibur = 0;
    map->tiles[x][y].mendiane = 0;
    map->tiles[x][y].phiras = 0;
    map->tiles[x][y].thystame = 0;
}

static void min_resource(map_t* map)
{
    map->foodMax <= 0 ? map->foodMax = 1 : 0;
    map->linemateMax <= 0 ? map->linemateMax = 1 : 0;
    map->deraumereMax <= 0 ? map->deraumereMax = 1 : 0;
    map->siburMax <= 0 ? map->siburMax = 1 : 0;
    map->mendianeMax <= 0 ? map->mendianeMax = 1 : 0;
    map->phirasMax <= 0 ? map->phirasMax = 1 : 0;
    map->thystameMax <= 0 ? map->thystameMax = 1 : 0;
}

void init_map_resources(server_t* server)
{
    int map_size = server->map->height * server->map->width;

    server->map->food = 0;
    server->map->linemate = 0;
    server->map->deraumere = 0;
    server->map->sibur = 0;
    server->map->mendiane = 0;
    server->map->phiras = 0;
    server->map->thystame = 0;
    server->map->foodMax = map_size * 0.5f;
    server->map->linemateMax = map_size * 0.3f;
    server->map->deraumereMax = map_size * 0.15f;
    server->map->siburMax = map_size * 0.1f;
    server->map->mendianeMax = map_size * 0.1f;
    server->map->phirasMax = map_size * 0.08f;
    server->map->thystameMax = map_size * 0.05f;
    min_resource(server->map);
}

void init_map(server_t* server, optinfo_t* args)
{
    server->map = malloc(sizeof(map_t));
    server->map->height = args->height;
    server->map->width = args->width;
    server->map->timeBuffer = 0;

    init_map_resources(server);
    server->map->tiles = malloc(sizeof(tile_t*) * (server->map->height + 1));

    for (int y = 0; y < server->map->height; y++) {
        server->map->tiles[y] = malloc(sizeof(tile_t) \
        * (server->map->width + 1));
        for (int x = 0; x < server->map->width; x++) {
            init_tile(server->map, y, x);
        }
    }
    server->map->tiles[server->map->height] = NULL;
    refill_resources(server, server->map);
}
