#pragma once

#include "core/ecs/system/system.hpp"
#include "core/ecs/coordinator.hpp"
#include "shared/components/components.hpp"
#include "core/transform/Transform.hpp"

namespace rtype::sys
{

    class UpdateAABB : public exng::sys::System
    {
    public:
        UpdateAABB(exng::Coordinator &coordinator) : System(coordinator) {}

        void update()
        {
            for (auto entity : mEntities) {
                auto& AABB = mCoordinator.getComponent<comp::AABB>(entity);
                auto& transform = mCoordinator.getComponent<comp::Transform>(entity);

                // transform the rect to the global space
                exng::Transform t = exng::Transform::Identity;
                t.translate(transform.getPosition());
                t.rotate(transform.getRotation());
                t.scale(transform.getScale());

                t.translate(-transform.getOrigin());

                AABB.globalBounds = t.transformRect(AABB.localBounds);
            }
        }
    };
}