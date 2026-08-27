/*
** EPITECH PROJECT, 2024
** B-CPP-500-STG-5-2-rtype-julian.lambert
** File description:
** SendPlayerInfo
*/

#pragma once

#include "core/ecs/system/system.hpp"
#include "core/ecs/coordinator.hpp"
#include "shared/components/components.hpp"
#include "core/transform/Transform.hpp"
#include "core/net/UDPServer.hpp"
#include "shared/include/protocol.h"

namespace rtype::sys
{

    class SendPlayerInfo : public exng::sys::System
    {
    public:
        SendPlayerInfo(exng::Coordinator &coordinator) : System(coordinator) {}

        void update(exng::net::UDPServer& server)
        {
            for (auto entity : mEntities) {
                auto& health = mCoordinator.getComponent<comp::Health>(entity);

                exng::net::Packet packet;
                packet << MessageType::PlayerInfo << health.hp << health.maxHp;
                server.notifyPacket(packet);
            }
        }
    };
}