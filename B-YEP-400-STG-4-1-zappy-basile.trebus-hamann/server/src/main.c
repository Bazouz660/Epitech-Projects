/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** main
*/

#include "server.h"

int main(int ac, const char **av)
{
    optinfo_t* args = get_args(ac, av);
    server_t srv = new_srv(INADDR_ANY, args);

    init_serv(&srv, args);
    free_args(&args);
    server_run(&srv);
    close_server(&srv);
    return 0;
}
