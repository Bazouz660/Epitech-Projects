/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** server
*/

#pragma once

#include "common.h"
#include "linked_list.h"

#define client_at(linked_list, index) ((client_t *)\
    (ll_get_node_by_index(linked_list, index)->data))

#define MAX_BUFFER_SIZE 1024

enum resource {
    FOOD,
    LINEMATE,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME
};

typedef struct {
    double freq;
    struct timeval start;
    struct timeval end;
    double tu;
} zpy_clock_t;

typedef struct optinfo_s {
    int port;
    int width;
    int height;
    int clientsNb;
    float freq;
    char **teamNames;
    int teamCount;
} optinfo_t;

typedef struct inventory_s {
    int food;
    int linemate;
    int deraumere;
    int sibur;
    int mendiane;
    int phiras;
    int thystame;
} inventory_t;

typedef struct session_s {
    int x;
    int y;
    int level;
    int num;
    int hp;
    int hp_max;
    int food_timer;
    bool should_disconnect;
    uuid_t uuid;
    float action_timer;
    char* team;
    enum orientation {
        NORTH,
        EAST,
        SOUTH,
        WEST
    } orientation;
    inventory_t *inventory;
} session_t;

typedef struct client_s {
    enum client_type {
        UNKNOWN,
        AI,
        GRAPHIC
    } type;
    struct sockaddr_in address;
    session_t* session;
    ll_node *command_list;
    int fd_con;
    int addr_len;
    bool authentified;
} client_t;

typedef struct tile_s {
    int food;
    int linemate;
    int deraumere;
    int sibur;
    int mendiane;
    int phiras;
    int thystame;
} tile_t;

typedef struct map_s {
    int height;
    int width;
    double timeBuffer;
    tile_t **tiles;
    int food;
    int foodMax;
    int linemate;
    int linemateMax;
    int deraumere;
    int deraumereMax;
    int sibur;
    int siburMax;
    int mendiane;
    int mendianeMax;
    int phiras;
    int phirasMax;
    int thystame;
    int thystameMax;
} map_t;

typedef struct team_s {
    char *name;
    client_t **clients;
    int nbcli;
} team_t;

typedef struct server_s {
    struct sockaddr_in address;
    struct timeval timeout;
    ll_node *clients;
    fd_set currentsock;
    team_t **teams;
    map_t *map;
    int cli_per_team;
    int maxcli;
    int fd_con;
    int addr_len;
    int port;
    int nbcli;
    zpy_clock_t *clock;
} server_t;

// init
optinfo_t* get_args(int argc, const char **argv);
void init_serv(server_t *server, optinfo_t* args);

void handlecmd(client_t *, server_t *);
void server_run(server_t *);
void update_set(server_t *);
server_t new_srv(in_addr_t, optinfo_t *);
session_t* newsess(void);
void sendmessage(client_t *, const char *);
bool authentify(client_t *client, server_t *server, char *command);
int dispatchcmd_ai(client_t* client, server_t* server, char** args);
bool check_command(client_t* client, char* command);

// team
bool team_exists(server_t *server, const char *team);
void add_team(server_t *server, const char *team);
team_t *get_team(server_t *server, const char *team_name);
void init_teams(server_t *server, optinfo_t *args);
void init_map(server_t *server, optinfo_t *args);
bool team_is_full(server_t *server, const char *team);
void add_team_cli(server_t *server, const char *team_name, client_t *client);
void notify_guis(server_t *server, const char *msg);
void notify_guis_cmd(server_t *server, void (*cmd)(client_t *,
server_t *, char **), char **args);

// client
void addcli(server_t *server);
session_t *get_session_by_num(server_t *server, int num);

// free
void disconnect_client(server_t *server, client_t *client);
void close_server(server_t *server);
void free_args(optinfo_t **args);

// map
void refill_resources(server_t *server, map_t *map);

// clock
double get_elapsed_time(server_t *server);
void init_clock(server_t *server, optinfo_t *args);

// logic
void update_logic(server_t *server);
bool can_perform(server_t* server, client_t *cli, float time);
