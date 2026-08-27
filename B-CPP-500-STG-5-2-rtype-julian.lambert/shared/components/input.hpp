#pragma once

#include "core/ecs/entity/entity.hpp"
#include "core/event/Keyboard.hpp"

namespace rtype::comp {

    struct InputStates
    {
        std::map<exng::Keyboard::Key, bool> m_keys;
    };

}