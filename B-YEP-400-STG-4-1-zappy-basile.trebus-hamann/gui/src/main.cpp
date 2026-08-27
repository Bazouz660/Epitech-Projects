/*
** EPITECH PROJECT, 2023
** B-YEP-400-STG-4-1-zappy-basile.trebus-hamann
** File description:
** main
*/

#include "GUI.hpp"

int main(int ac, char **av)
{
    zpy::GUI gui;

    if (ac != 3)
        return 84;

    try {
        gui.init(std::atoi(av[1]), av[2]);
        gui.run();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}