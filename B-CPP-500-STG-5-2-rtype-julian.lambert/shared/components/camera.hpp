/*
** EPITECH PROJECT, 2023
** B-CPP-500-STG-5-2-rtype-julian.lambert
** File description:
** camera
*/

#pragma once

#include "core/ecs/entity/entity.hpp"
#include "core/window/view/View.hpp"

namespace rtype::comp {

    struct Camera
    {
        exng::View view;

        exng::Entity target = NULL_ENTITY;
    };

}
