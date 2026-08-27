/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** ScrollingBackground
*/

#pragma once

#include "EntityFactory.hpp"

#include "shared/components/components.hpp"

#include "core/resource_manager/ResourceManager.hpp"

namespace rtype {

    class ScrollingBackground {
        public:
            ScrollingBackground()
            {
                space1.type = comp::Drawable::Type::SPRITE;
                space1.sprite.shape.setTexture(exng::ResourceManager::getTexture("texture", "background/stage1_background"));
                space1.sprite.shape.setTextureRect(sf::IntRect(0, 0, 1920, 1080));
                space1.sprite.shape.setPosition(0, 0);

                space2.type = comp::Drawable::Type::SPRITE;
                space2.sprite.shape.setTexture(exng::ResourceManager::getTexture("texture", "background/stage1_background"));
                space2.sprite.shape.setTextureRect(sf::IntRect(0, 0, 1920, 1080));
                space2.sprite.shape.setPosition(1920, 0);

                littleStars1.type = comp::Drawable::Type::SPRITE;
                littleStars1.sprite.shape.setTexture(exng::ResourceManager::getTexture("texture", "background/StarsSmall"));
                littleStars1.sprite.shape.setPosition(0, 0);

                littleStars2.type = comp::Drawable::Type::SPRITE;
                littleStars2.sprite.shape.setTexture(exng::ResourceManager::getTexture("texture", "background/StarsSmall"));
                littleStars2.sprite.shape.setTextureRect(sf::IntRect(0, 0, 1920, 1080));
                littleStars2.sprite.shape.setPosition(1920, 0);

                bigStars1.type = comp::Drawable::Type::SPRITE;
                bigStars1.sprite.shape.setTexture(exng::ResourceManager::getTexture("texture", "background/StarsBig_1"));
                bigStars1.sprite.shape.setTextureRect(sf::IntRect(0, 0, 1920, 1080));
                bigStars1.sprite.shape.setPosition(0, 0);

                bigStars2.type = comp::Drawable::Type::SPRITE;
                bigStars2.sprite.shape.setTexture(exng::ResourceManager::getTexture("texture", "background/StarsBig_1"));
                bigStars2.sprite.shape.setTextureRect(sf::IntRect(0, 0, 1920, 1080));
                bigStars2.sprite.shape.setPosition(1920, 0);

                space_speed = 20.0f;
                littleStars_speed = 40.0f;
                bigStars_speed = 60.0f;
            }

            ~ScrollingBackground();

            void update(float deltaTime)
            {
                space1.sprite.shape.move(-space_speed * deltaTime, 0);
                space2.sprite.shape.move(-space_speed * deltaTime, 0);

                littleStars1.sprite.shape.move(-littleStars_speed * deltaTime, 0);
                littleStars2.sprite.shape.move(-littleStars_speed * deltaTime, 0);

                bigStars1.sprite.shape.move(-bigStars_speed * deltaTime, 0);
                bigStars2.sprite.shape.move(-bigStars_speed * deltaTime, 0);

                if (space1.sprite.shape.getPosition().x < -1920)
                    space1.sprite.shape.setPosition(space2.sprite.shape.getPosition().x + 1920, 0);
                if (space2.sprite.shape.getPosition().x < -1920)
                    space2.sprite.shape.setPosition(space1.sprite.shape.getPosition().x + 1920, 0);


                if (littleStars1.sprite.shape.getPosition().x < -1920)
                    littleStars1.sprite.shape.setPosition(littleStars2.sprite.shape.getPosition().x + 1920, 0);
                if (littleStars2.sprite.shape.getPosition().x < -1920)
                    littleStars2.sprite.shape.setPosition(littleStars1.sprite.shape.getPosition().x + 1920, 0);

                if (bigStars1.sprite.shape.getPosition().x < -1920)
                    bigStars1.sprite.shape.setPosition(bigStars2.sprite.shape.getPosition().x + 1920, 0);
                if (bigStars2.sprite.shape.getPosition().x < -1920)
                    bigStars2.sprite.shape.setPosition(bigStars1.sprite.shape.getPosition().x + 1920, 0);
            }

            void draw(sf::RenderWindow &window)
            {
                window.draw(space1.sprite.shape);
                window.draw(space2.sprite.shape);

                window.draw(littleStars1.sprite.shape);
                window.draw(littleStars2.sprite.shape);

                window.draw(bigStars1.sprite.shape);
                window.draw(bigStars2.sprite.shape);
            }

        private:
            comp::Drawable space1;
            comp::Drawable space2;
            comp::Drawable littleStars1;
            comp::Drawable littleStars2;
            comp::Drawable bigStars1;
            comp::Drawable bigStars2;

            float space_speed;
            float littleStars_speed;
            float bigStars_speed;
    };
}


