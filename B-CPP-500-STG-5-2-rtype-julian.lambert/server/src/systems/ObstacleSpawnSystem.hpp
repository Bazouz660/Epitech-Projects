/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** ObstacleSpawnSystem
*/

#ifndef OBSTACLESPAWNSYSTEM_HPP_
#define OBSTACLESPAWNSYSTEM_HPP_

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

    class ObstacleSpawnSystem : public exng::sys::System
    {
        public:
            ObstacleSpawnSystem(exng::Coordinator &coordinator) : System(coordinator) {}

            void update(float dt, exng::net::UDPServer& UDPserver)
            {
                _time += dt;
                if (_time >= _spawnTime) {
                    _time = 0;
                    auto entity = constructors::createObstacle(mCoordinator, exng::context::getTargetResolution().x * 1.2, std::rand() % 2);
                    exng::net::Packet packet;
                    packet << MessageType::NewEntity << entity << EntityType::Obstacle;
                    UDPserver.reliableNotifyPacket(packet);
                }
            }

        private:
            float _time = 0;
            float _spawnTime = 3;


    };

}

#endif /* !OBSTACLESPAWNSYSTEM_HPP_ */
