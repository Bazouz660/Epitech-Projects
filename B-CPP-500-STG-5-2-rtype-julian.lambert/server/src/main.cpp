/*
** EPITECH PROJECT, 2023
** B-CPP-500-STG-5-2-rtype-julian.lambert
** File description:
** main
*/

#include "RTypeServer.hpp"
#include <thread>

int main()
{
    try {
        rtype::RTypeServer server;
        server.run();
    } catch (const std::exception &e) {
        exng::logger::error() << e.what();
    }
}