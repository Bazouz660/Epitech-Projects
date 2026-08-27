/*
** EPITECH PROJECT, 2024
** B-CPP-500-STG-5-2-rtype-julian.lambert
** File description:
** PlayerBoundariesSystem
*/


#ifndef RTYPE_PLAYERBOUNDARIESSYSTEM_HPP_
#define RTYPE_PLAYERBOUNDARIESSYSTEM_HPP_

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

    class PlayerBoundariesSystem : public exng::sys::System
    {
        public:
            PlayerBoundariesSystem(exng::Coordinator &coordinator) : System(coordinator) {}

            void update()
            {
                for (auto& entity : mEntities) {
                    auto& transform = mCoordinator.getComponent<comp::Transform>(entity);
                    auto& aabb = mCoordinator.getComponent<comp::AABB>(entity);

                    if (transform.getPosition().x < 0)
                        transform.setPosition(0, transform.getPosition().y);
                    if (transform.getPosition().x + aabb.globalBounds.width > exng::context::getTargetResolution().x)
                        transform.setPosition(exng::context::getTargetResolution().x - aabb.globalBounds.width, transform.getPosition().y);
                    if (transform.getPosition().y < 0)
                        transform.setPosition(transform.getPosition().x, 0);
                    if (transform.getPosition().y + aabb.globalBounds.height > exng::context::getTargetResolution().y)
                        transform.setPosition(transform.getPosition().x, exng::context::getTargetResolution().y - aabb.globalBounds.height);
                }
            }

    };

}

#endif /* !RTYPE_PLAYERBOUNDARIESSYSTEM_HPP_ */
