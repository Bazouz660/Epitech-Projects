#ifndef RTYPE_SPRITESHEETSYSTEM_HPP
#define RTYPE_SPRITESHEETSYSTEM_HPP

#include "shared/components/components.hpp"

#include "core/ecs/system/system.hpp"
#include "core/ecs/coordinator.hpp"
#include "helper/SafeDequeue.hpp"

namespace rtype::sys
{

    class SpriteSheetSystem : public exng::sys::System
    {
        public:
            SpriteSheetSystem(exng::Coordinator &coordinator) : System(coordinator) {}

            void update(float dt, exng::SafeDequeue<std::pair<exng::Entity, bool>>& entitiesToDestroy)
            {
                for (auto entity : mEntities) {
                    auto &spriteSheet = mCoordinator.getComponent<comp::SpriteSheet>(entity);
                    if (spriteSheet.destroyOnEnd && spriteSheet.sheet.isFinished()) {
                        entitiesToDestroy.push(std::make_pair(entity, true));
                        continue;
                    }
                    auto &drawable = mCoordinator.getComponent<comp::Drawable>(entity);
                    sf::IntRect frame;
                    frame.left = spriteSheet.sheet.getFrame().left;
                    frame.top = spriteSheet.sheet.getFrame().top;
                    frame.width = spriteSheet.sheet.getFrame().width;
                    frame.height = spriteSheet.sheet.getFrame().height;
                    drawable.sprite.shape.setTextureRect(frame);
                }
            }
    };

}

#endif // !RTYPE_SPRITESHEETSYSTEM_HPP