/*
** EPITECH PROJECT, 2024
** B-CPP-500-STG-5-2-rtype-julian.lambert
** File description:
** LaserSystem
*/

#pragma once

#include "core/ecs/system/system.hpp"
#include "core/ecs/coordinator.hpp"
#include "shared/components/components.hpp"
#include "core/net/UDPServer.hpp"
#include "shared/include/protocol.h"

namespace rtype::sys
{

    class LifetimeSystem : public exng::sys::System
    {
    public:
        LifetimeSystem(exng::Coordinator &coordinator) : System(coordinator) {}

        void update(exng::net::UDPServer& server, float dt, exng::SafeDequeue<exng::Entity>& entitiesToDestroy)
        {
            for (auto entity : mEntities) {
                auto& lifetime = mCoordinator.getComponent<comp::Lifetime>(entity);

                if (lifetime.exceeded)
                    continue;

                lifetime.maxtime -= dt;
                if (lifetime.maxtime <= 0) {
                    lifetime.exceeded = true;
                    entitiesToDestroy.push(entity);
                }
            }
        }
    };
}