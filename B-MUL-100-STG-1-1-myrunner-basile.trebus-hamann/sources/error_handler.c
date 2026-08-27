/*
** EPITECH PROJECT, 2021
** B-MUL-100-STG-1-1-myrunner-basile.trebus-hamann
** File description:
** error_handler.c
*/

#include "../includes/my_runner.h"

int error_handler(int argc, char **argv)
{
    int error_code = 1;

    if (argc < 2 || argc > 2) {
        write(2, "my_runner:\nbad usage: you must specify a map ", 45);
        write(2, "as argument, or -i for inf mode, or -h for usage.\n", 50);
        return 84;
    } else if (my_strcmp(argv[1], "-h") == 0) {
       read_usage();
       error_code = 0;
    }
    error_code += 0;
    if (error_code == 1
        && open(argv[1], 0, O_RDONLY) == -1 && my_strcmp(argv[1], "-i") != 0) {
        write(2, argv[1], my_strlen(argv[1]));
        write(2, ": error, no such file or directory\n", 35);
        error_code = 84;
    }
    if (my_strcmp(argv[1], "-i") == 0) {
        write(1, "-i is not implemented yet\n", 26);
        error_code = 0;
    }
    return error_code;
}
