/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** socket
*/

#include "server.h"
#include "sutils.h"

volatile sig_atomic_t stop_flag;

void handle_sigint(int signum)
{
    stop_flag = true;
}

void update_set(server_t* server)
{
    FD_ZERO(&server->currentsock);
    FD_SET(server->fd_con, &server->currentsock);

    for (int i = 0; i < server->nbcli; i++)
        FD_SET(client_at(server->clients, i)->fd_con, &server->currentsock);
}

int select_sock(server_t* server)
{
    return select(FD_SETSIZE, &server->currentsock, NULL,
        NULL, &server->timeout);
}

void handle_sock(server_t* server)
{
    for (int i = 0; i < server->nbcli; i++)
        if (FD_ISSET(client_at(server->clients, i)->fd_con,
            &server->currentsock))
            handlecmd(client_at(server->clients, i), server);
    if (FD_ISSET(server->fd_con, &server->currentsock))
        addcli(server);
}

void server_run(server_t* server)
{
    stop_flag = false;
    server->clients = NULL;
    server->nbcli = 0;
    signal(SIGINT, handle_sigint);
    while (!stop_flag) {
        update_set(server);
        if (select_sock(server) < 0)
            continue;
        handle_sock(server);
        update_logic(server);
    }
}
