#pragma once

#include "core/vector2/Vector2.hpp"

namespace rtype::comp {

    struct Rigidbody
    {
        exng::Vector2f velocity = {0.0f, 0.0f};
        exng::Vector2f acceleration = {0.0f, 0.0f};
        float mass = 1.0f;
        float friction = 0.0f;
        float restitution = 0.0f;
        bool isStatic = false;
    };

}
