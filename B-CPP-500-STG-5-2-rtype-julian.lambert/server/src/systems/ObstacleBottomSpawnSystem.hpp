/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** ObstacleBottomSpawnSystem
*/

#ifndef OBSTACLEBOTTOMSPAWNSYSTEM_HPP_
#define OBSTACLEBOTTOMSPAWNSYSTEM_HPP_

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

    class ObstacleBottomSpawnSystem : public exng::sys::System
    {
        public:
            ObstacleBottomSpawnSystem(exng::Coordinator &coordinator) : System(coordinator) {}

            void update(float dt, exng::net::UDPServer& UDPserver)
            {
                _time += dt;
                if (_time >= _spawnTime) {
                    _time = 0;
                    auto entity = constructors::createObstacleBottom(mCoordinator, exng::context::getTargetResolution().x * 1.2, exng::context::getTargetResolution().y - 132);
                    exng::net::Packet packet;
                    packet << MessageType::NewEntity << entity << EntityType::Obstacle_bottom;
                    UDPserver.reliableNotifyPacket(packet);
                }
            }

        private:
            float _time = 0;
            float _spawnTime = 3;

    };

}

#endif /* !OBSTACLEBOTTOMSPAWNSYSTEM_HPP_ */
