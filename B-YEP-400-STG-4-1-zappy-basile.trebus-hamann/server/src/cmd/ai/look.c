/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** look
*/

#include "server.h"
#include "sutils.h"

char *look_tile(server_t *server, int x, int y)
{
    char *str = NULL;

    //for (int i = 0; i < server->map->player; i++)
    //    str = svaprintf_wish("%s player", str);
    for (int i = 0; i < server->map->tiles[x][y].food; i++)
        str = svaprintf_wish("%s food", str);
    for (int i = 0; i < server->map->tiles[x][y].linemate; i++)
        str = svaprintf_wish("%s linemate", str);
    for (int i = 0; i < server->map->tiles[x][y].deraumere; i++)
        str = svaprintf_wish("%s deraumere", str);
    for (int i = 0; i < server->map->tiles[x][y].sibur; i++)
        str = svaprintf_wish("%s sibur", str);
    for (int i = 0; i < server->map->tiles[x][y].mendiane; i++)
        str = svaprintf_wish("%s mendiane", str);
    for (int i = 0; i < server->map->tiles[x][y].phiras; i++)
        str = svaprintf_wish("%s phiras", str);
    for (int i = 0; i < server->map->tiles[x][y].thystame; i++)
        str = svaprintf_wish("%s thystame", str);
    return (str);
}

int x_in_map(server_t *server, int x)
{
    if (x < 0)
        x = server->map->height - x;
    if (x > server->map->height)
        x = x - server->map->height;
    return x;
}

int y_in_map(server_t *server, int y)
{
    if (y < 0)
        y = server->map->width - y;
    if (y > server->map->width)
        y = y - server->map->width;
    return (y);
}

void look_north(client_t* client, server_t *server, int x, int y)
{
    char *str = NULL;
    char *str_tile = NULL;
    int x_look;
    int y_look;

    str = svaprintf_wish("[%s", look_tile(server, x, y));
    for (int i = 1, len_line = 3; i < 4; i++, len_line += 2) {
        for (int j = 0; j < len_line; j++) {
            x_look = x_in_map(server, (x - i));
            y_look = y_in_map(server, (y + j - i));
            str_tile = look_tile(server, x_look, y_look);
            str = svaprintf_wish("%s,%s", str, str_tile);
            free(str_tile);
        }
    }
    str = svaprintf_wish("%s]", str);
    sendmessage(client, str);
    free(str);
}

void look_east(client_t* client, server_t *server, int x, int y)
{
    char *str = NULL;
    char *str_tile = NULL;
    int x_look;
    int y_look;

    str = svaprintf_wish("[%s", look_tile(server, x, y));
    for (int j = 1, len_line = 3; j < 4; j++, len_line += 2) {
        for (int i = 0; i < len_line; i++) {
            x_look = x_in_map(server, (x + i - j));
            y_look = y_in_map(server, (y + j));
            str_tile = look_tile(server, x_look, y_look);
            str = svaprintf_wish("%s,%s", str, str_tile);
            free(str_tile);
        }
    }
    str = svaprintf_wish("%s]", str);
    sendmessage(client, str);
    free(str);
}

void look_south(client_t* client, server_t *server, int x, int y)
{
    char *str = NULL;
    char *str_tile = NULL;
    int x_look;
    int y_look;

    str = svaprintf_wish("[%s", look_tile(server, x, y));
    for (int i = 1, len_line = 3; i < 4; i++, len_line += 2) {
        for (int j = 0; j < len_line; j++) {
            x_look = x_in_map(server, (x + i));
            y_look = y_in_map(server, (y - j + i));
            str_tile = look_tile(server, x_look, y_look);
            str = svaprintf_wish("%s,%s", str, str_tile);
            free(str_tile);
        }
    }
    str = svaprintf_wish("%s]", str);
    sendmessage(client, str);
    free(str);
}

void look_west(client_t* client, server_t *server, int x, int y)
{
    char *str = NULL;
    char *str_tile = NULL;
    int x_look;
    int y_look;

    str = svaprintf_wish("[%s", look_tile(server, x, y));
    for (int j = 1, len_line = 3; j < 4; j++, len_line += 2) {
        for (int i = 0; i < len_line; i++) {
            x_look = x_in_map(server, (x - i + j));
            y_look = y_in_map(server, (y - j));
            str_tile = look_tile(server, x_look, y_look);
            str = svaprintf_wish("%s,%s", str, str_tile);
            free(str_tile);
        }
    }
    str = svaprintf_wish("%s]", str);
    sendmessage(client, str);
    free(str);
}

void look(client_t* client, server_t* server, char** args)
{
    switch (client->session->orientation) {
        case NORTH:
            look_north(client, server, client->session->x, client->session->y);
            break;
        case EAST:
            look_east(client, server, client->session->x, client->session->y);
            break;
        case SOUTH:
            look_south(client, server, client->session->x, client->session->y);
            break;
        case WEST:
            look_west(client, server, client->session->x, client->session->y);
            break;
    }
}