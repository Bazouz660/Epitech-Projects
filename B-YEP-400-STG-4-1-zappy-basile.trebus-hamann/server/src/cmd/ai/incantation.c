/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** incantation
*/

#include "server.h"

typedef struct incantation_requirements_s {
    int level;
    int nb_players;
    int linemate;
	int deraumere;
	int sibur;
	int mendiane;
	int phiras;
	int thystame;
} incantation_requirements_t;

static const struct incantation_requirements_s ic_req[] = {
	{ 1, 1, 1, 0, 0, 0, 0, 0 },
	{ 2, 2, 1, 1, 1, 0, 0, 0 },
	{ 3, 2, 2, 0, 1, 0, 2, 0 },
	{ 4, 4, 1, 1, 2, 0, 1, 0 },
	{ 5, 4, 1, 2, 1, 3, 0, 0 },
	{ 6, 6, 1, 2, 3, 0, 1, 0 },
	{ 7, 6, 2, 2, 2, 2, 2, 0 }
};

bool check_case_incantation(server_t *server, session_t *sess)
{
	struct incantation_requirements_s ir = ic_req[sess->level - 1];
	map_t *map = server->map;

	if (map->tiles[sess->x][sess->y].linemate >= ir.linemate * ir.nb_players
	&& map->tiles[sess->x][sess->y].deraumere >= ir.deraumere * ir.nb_players
	&& map->tiles[sess->x][sess->y].sibur >= ir.sibur * ir.nb_players
	&& map->tiles[sess->x][sess->y].mendiane >= ir.mendiane * ir.nb_players
	&& map->tiles[sess->x][sess->y].phiras >= ir.phiras * ir.nb_players
	&& map->tiles[sess->x][sess->y].thystame >= ir.thystame * ir.nb_players)
		return (true);
	return (false);
}

void delete_post_incantation(server_t *server, session_t *sess)
{
	struct incantation_requirements_s ir = ic_req[sess->level - 1];
	map_t *map = server->map;

	map->tiles[sess->x][sess->y].linemate -= ir.linemate * ir.nb_players;
	map->tiles[sess->x][sess->y].deraumere -= ir.deraumere * ir.nb_players;
	map->tiles[sess->x][sess->y].sibur -= ir.sibur * ir.nb_players;
	map->tiles[sess->x][sess->y].mendiane -= ir.mendiane * ir.nb_players;
	map->tiles[sess->x][sess->y].phiras -= ir.phiras * ir.nb_players;
	map->tiles[sess->x][sess->y].thystame -= ir.thystame * ir.nb_players;
}

void incantation(client_t* client, server_t* server, char** args)
{
	session_t *sess = client->session;
	char *msg = NULL;

	if (sess->level == 8) {
		msg = svaprintf_wish("Current level: %d", sess->level);
		sendmessage(client, msg);
		free(msg);
		return;
	}
	if (check_case_incantation(server, sess) == false) {
		msg = svaprintf_wish("ko");
		sendmessage(client, msg);
		free(msg);
		return;
	}
	delete_post_incantation(server, sess);
	sess->level++;
	msg = svaprintf_wish("Current level: %d", sess->level);
	sendmessage(client, msg);
	free(msg);
}