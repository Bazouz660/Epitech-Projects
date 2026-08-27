/*
** EPITECH PROJECT, 2023
** B-CPP-500-STG-5-2-rtype-julian.lambert
** File description:
** RenderSystem
*/

#ifndef RTYPE_RENDERSYSTEM_HPP
#define RTYPE_RENDERSYSTEM_HPP

#include "shared/components/components.hpp"

#include "core/ecs/system/system.hpp"
#include "core/ecs/coordinator.hpp"

namespace rtype::sys
{

    class RenderSystem : public exng::sys::System
    {
        public:
            RenderSystem(exng::Coordinator &coordinator) : System(coordinator) {}

            void render(exng::Window &window)
            {
                std::vector<std::pair<exng::Entity, unsigned int>> sortedEntities;

                for (auto &entity : mEntities) {
                    unsigned int zIndex = 0;
                    if (!mCoordinator.hasComponent<comp::zIndex>(entity))
                        zIndex = mCoordinator.getComponent<comp::zIndex>(entity).zIndex;

                    sortedEntities.push_back(std::make_pair(entity, zIndex));
                }

                // Sort entities by zIndex
                std::sort(sortedEntities.begin(), sortedEntities.end(), [](const std::pair<exng::Entity, unsigned int> &a, const std::pair<exng::Entity, unsigned int> &b) {
                    return a.second < b.second;
                });

                for (auto &[entity, zIndex] : sortedEntities) {
                    auto &transform = mCoordinator.getComponent<comp::Transform>(entity);
                    auto &drawable = mCoordinator.getComponent<comp::Drawable>(entity);

                    sf::RenderStates states = sf::RenderStates::Default;
                    states.transform.translate(transform.getPosition().x, transform.getPosition().y);
                    states.transform.translate(-transform.getOrigin().x, -transform.getOrigin().y);
                    states.transform.rotate(transform.getRotation());
                    states.transform.scale(transform.getScale().x, transform.getScale().y);
                    states.transform.translate(transform.getOrigin().x, transform.getOrigin().y);

                    switch (drawable.type) {
                        case comp::Drawable::Type::RECTANGLE:
                            window.draw(drawable.rectangle.shape, states);
                            break;
                        case comp::Drawable::Type::CIRCLE:
                            window.draw(drawable.circle.shape, states);
                            break;
                        case comp::Drawable::Type::SPRITE:
                            window.draw(drawable.sprite.shape, states);
                            break;
                        case comp::Drawable::Type::TEXT:
                            window.draw(drawable.text.shape, states);
                            break;
                        case comp::Drawable::Type::VERTEX_BUFFER:
                            window.draw(drawable.vertexBuffer.shape, states);
                            break;
                    }
                }
            }
    };

}

#endif // !RTYPE_RENDERSYSTEM_HPP