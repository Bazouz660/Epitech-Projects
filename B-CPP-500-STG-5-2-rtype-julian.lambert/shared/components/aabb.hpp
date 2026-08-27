#pragma once

#include "core/rect/Rect.hpp"

namespace rtype::comp {

    struct AABB
    {
        exng::FloatRect localBounds;
        exng::FloatRect globalBounds;
    };

}
