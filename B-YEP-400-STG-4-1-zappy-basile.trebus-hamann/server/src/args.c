/*
** EPITECH PROJECT, 2023
** B-YEP-400-STG-4-1-zappy-basile.trebus-hamann
** File description:
** args
*/

#include "server.h"
#include "sutils.h"

static void print_usage(void)
{
    char *usage = "USAGE: ./zappy_server -p port -x width -y height "
            "-n name1 name2 ... -c clientsNb -f freq\n\n"
            "\tport is the port number\n"
            "\twidth is the width of the world\n"
            "\theight is the height of the world\n"
            "\tnameX is the name of the team X\n"
            "\tclientsNb is the number of authorized clients per team\n"
            "\tfreq is the reciprocal of time unit for execution of actions\n";

    dprintf(2, "%s", usage);
}

optinfo_t* new_optinfo(void)
{
    optinfo_t *optinfo = malloc(sizeof(optinfo_t));

    optinfo->port = 0;
    optinfo->width = 0;
    optinfo->height = 0;
    optinfo->teamCount = 0;
    optinfo->clientsNb = 0;
    optinfo->freq = 0;
    optinfo->teamNames = NULL;
    return optinfo;
}

static void get_team_names(optinfo_t *optinfo, int argc, const char **argv)
{
    optind--;
    for (; optind < argc && *argv[optind] != '-'; optind++) {
        optinfo->teamNames = realloc(optinfo->teamNames,
            sizeof(char *) * (optinfo->teamCount + 2));
        optinfo->teamNames[optinfo->teamCount++] = strdup(argv[optind]);
        optinfo->teamNames[optinfo->teamCount] = NULL;
    }
}

void check_mandatory(optinfo_t *optinfo)
{
    if (optinfo->port == 0 || optinfo->width == 0 || optinfo->height == 0 ||
        optinfo->teamCount == 0 || optinfo->clientsNb == 0
        || optinfo->freq == 0) {
        print_usage();
        free_arr(optinfo->teamNames);
        exit(84);
    }
}

optinfo_t* get_args(int argc, const char **argv)
{
    optinfo_t *optinfo = new_optinfo();
    char *optstring = "p:x:y:n:c:f:";
    int option;

    while ((option = getopt(argc, (char *const *) argv, optstring)) != -1) {
        if (option == 'p')
            optinfo->port = atoi(optarg);
        if (option == 'x')
            optinfo->width = atoi(optarg);
        if (option == 'y')
            optinfo->height = atoi(optarg);
        if (option == 'n')
            get_team_names(optinfo, argc, argv);
        if (option == 'c')
            optinfo->clientsNb = atoi(optarg);
        if (option == 'f')
            optinfo->freq = atof(optarg);
    }
    check_mandatory(optinfo);
}
