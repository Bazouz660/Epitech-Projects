#pragma once

#include "core/ecs/system/system.hpp"
#include "core/ecs/coordinator.hpp"
#include "shared/components/components.hpp"
#include "core/transform/Transform.hpp"
#include "core/net/UDPServer.hpp"
#include "shared/include/protocol.h"

namespace rtype::sys
{

    class SendNetData : public exng::sys::System
    {
    public:
        SendNetData(exng::Coordinator &coordinator) : System(coordinator) {}

        void update(exng::net::UDPServer& server)
        {
            for (auto entity : mEntities) {
                auto& transform = mCoordinator.getComponent<comp::Transform>(entity);

                exng::net::Packet packet;
                exng::Vector2f position = transform.getPosition();
                float rotation = transform.getRotation();
                exng::Vector2f velocity = {0, 0};

                if (mCoordinator.hasComponent<comp::Rigidbody>(entity)) {
                    auto& rigidbody = mCoordinator.getComponent<comp::Rigidbody>(entity);
                    velocity = rigidbody.velocity;
                }

                packet << MessageType::EntityPositionUpdate << entity << position.x << position.y << velocity.x << velocity.y << rotation;
                server.notifyPacket(packet);

                if (mCoordinator.hasComponent<comp::AABB>(entity)) {
                    auto& aabb = mCoordinator.getComponent<comp::AABB>(entity);
                    auto bounds = aabb.globalBounds;
                    exng::net::Packet packet2;
                    packet2 << MessageType::EntityHitboxUpdate << entity << bounds.width << bounds.height;
                    server.notifyPacket(packet2);
                }
            }
        }
    };
}