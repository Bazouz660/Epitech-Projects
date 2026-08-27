#pragma once

#include "core/ecs/system/system.hpp"
#include "core/ecs/coordinator.hpp"
#include "shared/components/components.hpp"

namespace rtype::sys
{

    class UpdateTransform : public exng::sys::System
    {
    public:
        UpdateTransform(exng::Coordinator &coordinator) : System(coordinator) {}

        void update()
        {
            for (auto entity : mEntities) {
                updateEntity(entity);
            }
        }

    private:
        void updateEntity(exng::Entity entity)
        {
            auto& transform = mCoordinator.getComponent<comp::Transform>(entity);

            if (!transform.getChildren().empty()) {
                transform.mGlobalPosition = transform.getLocalPosition();
                transform.mGlobalRotation = transform.getLocalRotation();
                transform.mGlobalScale = transform.getLocalScale();
            }

            for (auto child : transform.getChildren()) {
                auto& childTransform = mCoordinator.getComponent<comp::Transform>(child.entity);

                if (child.relativePosition) {
                    childTransform.mGlobalPosition = transform.mGlobalPosition + child.offset;
                }
                if (child.relativeRotation) {
                    childTransform.mGlobalRotation = transform.mGlobalRotation + childTransform.getLocalRotation();
                }
                if (child.relativeScale) {
                    childTransform.mGlobalScale = exng::Vector2f(transform.mGlobalScale.x * childTransform.getLocalScale().x, transform.mGlobalScale.y * childTransform.getLocalScale().y);
                }

                updateEntity(child.entity);
            }
        }
    };
}