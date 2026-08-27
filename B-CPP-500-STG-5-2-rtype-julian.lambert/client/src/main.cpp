/*
** EPITECH PROJECT, 2023
** B-CPP-500-STG-5-2-rtype-julian.lambert
** File description:
** main
*/

#include "RTypeClient.hpp"

int main()
{
    rtype::RTypeClient client;

    try {
        client.run();
    } catch (const std::exception &e) {
        exng::logger::error() << e.what();
    }
    return 0;
}