/*
** EPITECH PROJECT, 2024
** B-CPP-500-STG-5-2-rtype-julian.lambert
** File description:
** onDestruction
*/

#ifndef EXNG_COMPONENTS_ONDESTRUCTION_HPP
#define EXNG_COMPONENTS_ONDESTRUCTION_HPP

#include <functional>

namespace rtype::comp {

    struct OnDestruction {
        std::function<void()> callback;
    };

}

#endif //EXNG_COMPONENTS_ONDESTRUCTION_HPP