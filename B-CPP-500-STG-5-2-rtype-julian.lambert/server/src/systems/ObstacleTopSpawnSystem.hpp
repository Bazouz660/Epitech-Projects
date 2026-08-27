/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** ObstacleTopSpawnSystem
*/

#ifndef OBSTACLETOPSPAWNSYSTEM_HPP_
#define OBSTACLETOPSPAWNSYSTEM_HPP_

#include "shared/components/components.hpp"

#include "core/ecs/system/system.hpp"
#include "core/ecs/coordinator.hpp"
#include "helper/SafeDequeue.hpp"
#include "server/include/entityConstructors.h"
#include "helper/info/context.hpp"

#include "core/net/UDPServer.hpp"
#include "shared/include/protocol.h"

namespace rtype::sys
{

    class ObstacleTopSpawnSystem : public exng::sys::System
    {
        public:
            ObstacleTopSpawnSystem(exng::Coordinator &coordinator) : System(coordinator) {}

            void update(float dt, exng::net::UDPServer& UDPserver)
            {
                _time += dt;

                if (_time >= _spawnTime) {
                    _time = 0;
                    auto entity = constructors::createObstacleTop(mCoordinator, exng::context::getTargetResolution().x * 1.2, 0);
                    exng::net::Packet packet;
                    packet << MessageType::NewEntity << entity << EntityType::Obstacle_top;
                    UDPserver.reliableNotifyPacket(packet);
                }
            }

        private:
            float _time = 0;
            float _spawnTime = 4;

    };

}

#endif /* !OBSTACLETOPSPAWNSYSTEM_HPP_ */
