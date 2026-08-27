/*
** EPITECH PROJECT, 2024
** B-CPP-500-STG-5-2-rtype-julian.lambert
** File description:
** stats
*/

#pragma once

#include <chrono>

namespace rtype::comp {

    struct Health
    {
        int maxHp = 100;
        int hp = 100;
        float cooldown = 0.5;
        float cooldownTimeLeft = 0;
    };

    struct Damage
    {
        int val = 10;
    };

    struct Speed
    {
        float val = 100;
    };

    struct Team
    {
        int val = 0;
    };

    struct ShootingSpeed
    {
        float cooldown = 0.5;
        float timeLeft = 0;
    };

    struct Name
    {
        std::string val = "";
    };

}