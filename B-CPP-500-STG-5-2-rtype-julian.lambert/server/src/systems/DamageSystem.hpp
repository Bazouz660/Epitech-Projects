/*
** EPITECH PROJECT, 2024
** B-CPP-500-STG-5-2-rtype-julian.lambert
** File description:
** CollisionSystem
*/

#ifndef RTYPE_SERVER_DAMAGE_SYSTEM_HPP
#define RTYPE_SERVER_DAMAGE_SYSTEM_HPP

// engine includes
#include "core/ecs/system/system.hpp"
#include "core/ecs/coordinator.hpp"
#include "helper/SafeDequeue.hpp"
#include "helper/info/logger.hpp"

// server includes
#include "shared/components/components.hpp"
#include "shared/include/protocol.h"

namespace rtype::sys
{

    // handles collisions between entities to destroy them or apply damage
    class DamageSystem : public exng::sys::System
    {
        public:
            DamageSystem(exng::Coordinator &coordinator) : System(coordinator) {}

            void update(float dt, exng::SafeDequeue<exng::Entity> &entitiesToDestroy)
            {
                for (auto entity : mEntities) {
                    auto& aabb = mCoordinator.getComponent<comp::AABB>(entity);

                    for (auto other : mEntities) {
                        if (entity == other)
                            continue;

                        auto& otherAABB = mCoordinator.getComponent<comp::AABB>(other);

                        if (mCoordinator.hasComponent<comp::Team>(entity) && mCoordinator.hasComponent<comp::Team>(other)) {
                            auto& team = mCoordinator.getComponent<comp::Team>(entity);
                            auto& otherTeam = mCoordinator.getComponent<comp::Team>(other);

                            if (team.val == otherTeam.val)
                                continue;
                        }

                        if (mCoordinator.hasComponent<comp::Health>(other)) {
                            auto& cooldown = mCoordinator.getComponent<comp::Health>(other).cooldown;
                            auto& timer = mCoordinator.getComponent<comp::Health>(other).cooldownTimeLeft;
                            timer -= dt;
                        }

                        if (aabb.globalBounds.intersects(otherAABB.globalBounds)) {
                            if (mCoordinator.hasComponent<comp::Damage>(entity) && mCoordinator.hasComponent<comp::Health>(other)) {
                                auto& cooldown = mCoordinator.getComponent<comp::Health>(other).cooldown;
                                auto& timer = mCoordinator.getComponent<comp::Health>(other).cooldownTimeLeft;
                                if (timer <= 0) {
                                    timer = cooldown;
                                    auto& damage = mCoordinator.getComponent<comp::Damage>(entity);
                                    auto& health = mCoordinator.getComponent<comp::Health>(other);

                                    health.hp -= damage.val;
                                    if (health.hp <= 0) {
                                        entitiesToDestroy.push(other);
                                    }
                                }
                            }
                        }
                    }
                }
            }
    };
}

#endif //RTYPE_SERVER_DAMAGE_SYSTEM_HPP