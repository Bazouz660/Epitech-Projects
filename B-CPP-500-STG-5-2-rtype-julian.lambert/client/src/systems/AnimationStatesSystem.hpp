/*
** EPITECH PROJECT, 2024
** B-CPP-500-STG-5-2-rtype-julian.lambert
** File description:
** AnimationStatesSystem
*/

#ifndef RTYPE_ANIMATIONSTATESSYSTEM_HPP
#define RTYPE_ANIMATIONSTATESSYSTEM_HPP

#include "shared/components/components.hpp"

#include "core/ecs/system/system.hpp"
#include "core/ecs/coordinator.hpp"
#include "helper/SafeDequeue.hpp"

namespace rtype::sys
{

    class AnimationStatesSystem : public exng::sys::System
    {
        public:
            AnimationStatesSystem(exng::Coordinator &coordinator) : System(coordinator) {}

            void update(float dt)
            {
                for (auto entity : mEntities) {
                    auto &animStates = mCoordinator.getComponent<comp::AnimationStates>(entity);
                    auto &spriteSheet = mCoordinator.getComponent<comp::SpriteSheet>(entity);

                    if (mCoordinator.hasComponent<comp::Rigidbody>(entity) && mCoordinator.hasComponent<comp::PlayerTag>(entity)) {
                        auto &rigidbody = mCoordinator.getComponent<comp::Rigidbody>(entity);
                        if (rigidbody.velocity.y == 0 && animStates.states.getCurrentStateName() != "idle") {
                            animStates.states.setState("idle");
                        } else if (rigidbody.velocity.y > 0 && animStates.states.getCurrentStateName() != "down") {
                            animStates.states.setState("down");
                        } else if (rigidbody.velocity.y < 0 && animStates.states.getCurrentStateName() != "up") {
                            animStates.states.setState("up");
                        }
                    }

                    animStates.states.update(dt);
                    spriteSheet.sheet = animStates.states.getCurrentState();
                }
            }
    };

}

#endif // !RTYPE_ANIMATIONSTATESSYSTEM_HPP