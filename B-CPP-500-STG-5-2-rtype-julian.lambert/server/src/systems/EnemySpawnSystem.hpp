/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** EnnemySpawnSystem
*/

#ifndef ENEMYSPAWNSYSTEM_HPP_
#define ENEMYSPAWNSYSTEM_HPP_

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

    class EnemySpawnSystem : public exng::sys::System
    {
        public:
            EnemySpawnSystem(exng::Coordinator &coordinator) : System(coordinator) {}

            void update(float dt, exng::net::UDPServer& UDPserver)
            {
                _time += dt;
                if (_time >= _spawnTime) {
                    _time = 0;
                    auto batOrSnake = std::rand() % 10;
                    exng::Entity entity;
                    exng::net::Packet packet;
                    //if (batOrSnake == 0) {
                   //     entity = constructors::createSnake(mCoordinator, exng::context::getTargetResolution().x * 1.2, std::rand() % int(exng::context::getTargetResolution().y * 0.8), 3);
                    //    packet << MessageType::NewEntity << entity << EntityType::Snake;
                   // } else {
                        entity = constructors::createBatEnemy(mCoordinator, exng::context::getTargetResolution().x * 1.2, std::rand() % int(exng::context::getTargetResolution().y * 0.8), 400);
                        packet << MessageType::NewEntity << entity << EntityType::BatEnemy;
                    //}
                    UDPserver.reliableNotifyPacket(packet);
                }
            }

        private:
            float _time = 0;
            float _spawnTime = 1;


    };

}

#endif /* !ENNEMYSPAWNSYSTEM_HPP_ */
