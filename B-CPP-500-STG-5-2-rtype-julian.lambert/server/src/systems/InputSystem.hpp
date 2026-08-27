#pragma once

#include "system.hpp"
#include "coordinator.hpp"
#include "shared/components/components.hpp"
#include "core/net/UDPServer.hpp"
#include "helper/info/logger.hpp"
#include <cmath>


#include "server/include/entityConstructors.h"
#include "server/include/teams.h"

#include "core/event/Keyboard.hpp"

#include "shared/include/protocol.h"

namespace rtype::sys
{

    class InputSystem : public exng::sys::System
    {
    public:
        InputSystem(exng::Coordinator &coordinator) : System(coordinator) {}

        void update(float dt, exng::net::UDPServer& server)
        {
            for (auto entity : mEntities)
            {
                auto &inputQueue = mCoordinator.getComponent<comp::InputStates>(entity);
                auto &networkID = mCoordinator.getComponent<comp::NetworkIdentity>(entity);
                auto &rigidBody = mCoordinator.getComponent<comp::Rigidbody>(entity);
                auto &transform = mCoordinator.getComponent<comp::Transform>(entity);
                auto &shootingSpeed = mCoordinator.getComponent<comp::ShootingSpeed>(entity);

                for (auto &[key, pressed] : inputQueue.m_keys)
                {
                    if (!pressed)
                        continue;

                    if (key == exng::Keyboard::Up) {
                        rigidBody.acceleration.y -= 10;
                    }
                    else if (key == exng::Keyboard::Down) {
                        rigidBody.acceleration.y += 10;
                    }
                    else if (key == exng::Keyboard::Left) {
                        rigidBody.acceleration.x -= 10;
                    }
                    else if (key == exng::Keyboard::Right) {
                        rigidBody.acceleration.x += 10;
                    } else if (key == exng::Keyboard::Space) {
                        if (shootingSpeed.timeLeft > 0)
                            continue;
                        shootingSpeed.timeLeft = shootingSpeed.cooldown;
                        exng::Entity entity = constructors::createLaser(mCoordinator, transform.getPosition().x, transform.getPosition().y, teams::Players);
                        exng::net::Packet response;
                        response << MessageType::NewEntity << entity << EntityType::Laser;
                        server.reliableNotifyPacket(response);

                    }
                }

                if (shootingSpeed.timeLeft > 0)
                    shootingSpeed.timeLeft -= dt;
            }
        }
    };
}
