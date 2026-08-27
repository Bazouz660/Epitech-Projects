/*
** EPITECH PROJECT, 2024
** B-CPP-500-STG-5-2-rtype-julian.lambert
** File description:
** spritesheet
*/

#ifndef SPRITESHEET_HPP_
#define SPRITESHEET_HPP_

#include "core/ecs/entity/entity.hpp"
#include "core/window/view/View.hpp"
#include "engine/src/core/effects/SpriteSheet.hpp"
#include "engine/src/core/effects/AnimationStates.hpp"

namespace rtype::comp {

    struct SpriteSheet
    {
        exng::effect::SpriteSheet sheet;
        bool destroyOnEnd = false;
    };

    struct AnimationStates
    {
        exng::effect::AnimationStates states;
    };

}

#endif /* !SPRITESHEET_HPP_ */
