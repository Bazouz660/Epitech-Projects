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
#include "helper/info/context.hpp"

namespace rtype::sys
{

    class EntityDestroyer : public exng::sys::System
    {
    public:
        EntityDestroyer(exng::Coordinator &coordinator) : System(coordinator) {}

        void update(exng::net::UDPServer& server, exng::SafeDequeue<exng::Entity>& entitiesToDestroy, std::mutex& mutex)
        {
            for (auto entity : mEntities) {
                if (mCoordinator.hasComponent<comp::Transform>(entity) && mCoordinator.hasComponent<comp::AABB>(entity)) {
                    auto& transform = mCoordinator.getComponent<comp::Transform>(entity);
                    auto& aabb = mCoordinator.getComponent<comp::AABB>(entity);
                    if (200 + transform.getPosition().x + aabb.globalBounds.width < 0) {

                            bool alreadyInQueue = std::find(entitiesToDestroy.begin(), entitiesToDestroy.end(), entity) != entitiesToDestroy.end();

                            if (!alreadyInQueue)
                                entitiesToDestroy.push(entity);
                    }
                }
            }

            while (!entitiesToDestroy.empty()) {
                auto entity = entitiesToDestroy.front();
                try {
                    mCoordinator.destroyEntity(entity);
                } catch (std::exception& e) {
                }
                exng::net::Packet packet;
                packet << MessageType::EntityDestroyed << entity;
                server.reliableNotifyPacket(packet);
                entitiesToDestroy.pop();
            }
        }
    };
}