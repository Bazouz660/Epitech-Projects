/*
** EPITECH PROJECT, 2023
** B-CPP-500-STG-5-2-rtype-julian.lambert
** File description:
** CameraSystem
*/

#pragma once

#include "core/ecs/system/system.hpp"
#include "core/ecs/coordinator.hpp"
#include "shared/components/components.hpp"
#include "core/window/view/View.hpp"

namespace rtype::sys
{

    class CameraSystem : public exng::sys::System
    {
    public:
        CameraSystem(exng::Coordinator &coordinator) : System(coordinator) {}

        void update(float dt)
        {
            for (auto entity : mEntities) {
                auto& camera = mCoordinator.getComponent<comp::Camera>(entity);
                auto& targetTransform = mCoordinator.getComponent<comp::Transform>(camera.target);

                exng::Vector2f targetPosition = targetTransform.getPosition();
                exng::Vector2f cameraPosition = camera.view.getCenter();

                // cubic interpolation
                exng::Vector2f newPosition = cameraPosition + (targetPosition - cameraPosition) * dt * 10.f;
                camera.view.setCenter(newPosition);
            }
        }
    };

}