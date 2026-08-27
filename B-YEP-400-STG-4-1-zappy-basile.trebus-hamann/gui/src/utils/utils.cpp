/*
** EPITECH PROJECT, 2023
** B-YEP-400-STG-4-1-zappy-basile.trebus-hamann
** File description:
** utils
*/

#include "utils.hpp"

namespace zpy {

    namespace utils {
        Color getRandomColor() {
            Color c =
            {
                GetRandomValue(0, 255),
                GetRandomValue(0, 255),
                GetRandomValue(0, 255),
                255
            };
            return c;
        }
    }

}