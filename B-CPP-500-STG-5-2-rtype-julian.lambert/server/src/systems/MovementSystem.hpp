#pragma once

#include "core/ecs/system/system.hpp"
#include "core/ecs/coordinator.hpp"
#include "shared/components/components.hpp"
#include "helper/math/math.hpp"

namespace rtype::sys
{

    class MovementSystem : public exng::sys::System
    {
    public:
        MovementSystem(exng::Coordinator &coordinator) : System(coordinator) {}

        void update(float dt)
        {
            for (auto entity : mEntities) {
                auto& transform = mCoordinator.getComponent<comp::Transform>(entity);
                auto& rigidBody = mCoordinator.getComponent<comp::Rigidbody>(entity);

                int speed = 100;
                if (mCoordinator.hasComponent<comp::Speed>(entity)) {
                    speed = mCoordinator.getComponent<comp::Speed>(entity).val;
                }

                exng::Vector2f oldVelocity = rigidBody.velocity;

                float invMass = rigidBody.mass > 0 ? 1.f / rigidBody.mass : 0.f;

                // apply speed to acceleration
                rigidBody.acceleration *= speed;

                rigidBody.velocity += rigidBody.acceleration * invMass * dt;

                // apply friction (friction is a value between 0 and 1)
                rigidBody.velocity *= std::pow(1.0f - rigidBody.friction, dt * 3.f);

                exng::Vector2f avgVelocity = (rigidBody.velocity + oldVelocity) * 0.5f;
                transform.move(avgVelocity * dt);

                rigidBody.acceleration = exng::Vector2f(0.f, 0.f);
            }
        }
    };
}