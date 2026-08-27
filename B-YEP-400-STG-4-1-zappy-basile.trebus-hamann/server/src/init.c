/*
** EPITECH PROJECT, 2023
** B-YEP-400-STG-4-1-zappy-basile.trebus-hamann
** File description:
** session
*/

#include "server.h"
#include "sutils.h"

server_t new_srv(in_addr_t ip, optinfo_t *args)
{
    server_t server;
    server.maxcli = 10;
    server.addr_len = sizeof(server.address);
    if ((server.fd_con = socket(AF_INET, SOCK_STREAM, 0)) == 0)
        exit(ERR_EX);
    server.address.sin_addr.s_addr = htonl(ip);
    server.address.sin_port = htons(args->port);
    server.address.sin_family = AF_INET;
    server.timeout.tv_sec = 0;
    server.timeout.tv_usec = 0;
    setsockopt(server.fd_con, SOL_SOCKET, SO_REUSEADDR, &(int){1},
        sizeof(int));
    if (bind(server.fd_con, (struct sockaddr *)&server.address,
        sizeof(server.address)))
        exit(ERR_EX);
    if (listen(server.fd_con, server.maxcli) < 0)
        exit(ERR_EX);
    return server;
}

void init_serv(server_t *server, optinfo_t *args)
{
    server->port = args->port;
    server->cli_per_team = args->clientsNb;

    init_clock(server, args);
    init_teams(server, args);
    init_map(server, args);

    dprintf(2, "nb teams: %ld\n", get_arr_len((void *)server->teams));
    dprintf(2, "nb clients per team: %d\n", server->cli_per_team);
    for (int i = 0; server->teams[i]; i++)
        dprintf(2, "team: %s\n", server->teams[i]->name);
}
