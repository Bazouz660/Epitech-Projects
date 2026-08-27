/*
** EPITECH PROJECT, 2024
** B-CPP-500-STG-5-2-rtype-julian.lambert
** File description:
** entityConstructors
*/

#include "EntityFactory.hpp"
#include "shared/components/components.hpp"
#include "core/resource_manager/ResourceManager.hpp"
#include "core/rect/Rect.hpp"
#include "helper/info/context.hpp"

namespace rtype::constructors {

    exng::Entity createNameTag(exng::Coordinator &coordinator, const sf::Color& color, const std::string& name) {
        exng::Entity id = coordinator.createEntity();

        comp::Drawable drawable;
        drawable.type = comp::Drawable::Type::TEXT;
        drawable.text.shape.setFont(exng::ResourceManager::getFont("font", "upheavtt"));
        drawable.text.shape.setCharacterSize(20);
        drawable.text.shape.setFillColor(color);
        drawable.text.shape.setString(name);

        comp::zIndex zIndex;
        zIndex.zIndex = 2;

        comp::Transform transform;

        coordinator.addComponent(id, transform);
        coordinator.addComponent(id, drawable);
        coordinator.addComponent(id, zIndex);

        return id;
    }

    exng::Entity createHitbox(exng::Coordinator &coordinator)
    {
        exng::Entity id = coordinator.createEntity();

        comp::Transform transform;
        transform.setPosition({0.f, 0.f});
        transform.setScale({1.f, 1.f});
        transform.setRotation(0.f);

        comp::Drawable drawable;
        drawable.type = comp::Drawable::Type::RECTANGLE;
        drawable.rectangle.shape.setSize({0.f, 0.f});
        drawable.rectangle.shape.setFillColor(sf::Color::Transparent);
        //drawable.rectangle.shape.setOutlineColor(sf::Color(255, 0, 0, 200));
        drawable.rectangle.shape.setOutlineColor(sf::Color::Transparent);
        drawable.rectangle.shape.setOutlineThickness(1.f);

        comp::zIndex zIndex;
        zIndex.zIndex = 2;

        comp::AABB aabb;

        coordinator.addComponent(id, transform);
        coordinator.addComponent(id, drawable);
        coordinator.addComponent(id, zIndex);
        coordinator.addComponent(id, aabb);
        coordinator.addComponent(id, comp::ClientEntity());

        return id;
    }

    exng::Entity createLargeExplosion(exng::Coordinator &coordinator, exng::Vector2f position)
    {
        exng::Entity id = coordinator.createEntity();

        comp::Transform transform;
        transform.setPosition(position);
        transform.setScale({3.f, 3.f});
        transform.setRotation(0.f);

        comp::Drawable drawable;
        drawable.type = comp::Drawable::Type::SPRITE;
        drawable.sprite.shape.setTexture(exng::ResourceManager::getTexture("effect", "explosion_large"));
        auto size = drawable.sprite.shape.getTexture()->getSize();
        auto width = size.x / 6;
        auto height = size.y;
        drawable.sprite.shape.setTextureRect(sf::IntRect(width * 0, 0, width, height));

        comp::SpriteSheet spriteSheet;
        for (int i = 0; i < 6; i++)
            spriteSheet.sheet.addFrame(exng::IntRect(width * i, 0, width, height), 0.16f);
        spriteSheet.sheet.setLoop(false);
        spriteSheet.destroyOnEnd = true;

        comp::AnimationStates animationStates;
        animationStates.states.addState("explosion", spriteSheet.sheet, false);
        animationStates.states.setState("explosion");

        comp::zIndex zIndex;
        zIndex.zIndex = 1;

        comp::Sound sound;
        sound.sound = std::make_shared<sf::Sound>();
        sound.sound->setBuffer(exng::ResourceManager::getSoundBuffer("sound", "explosion_small"));
        sound.sound->setVolume(100.f);
        sound.sound->play();

        coordinator.addComponent(id, transform);
        coordinator.addComponent(id, drawable);
        coordinator.addComponent(id, zIndex);
        coordinator.addComponent(id, sound);
        coordinator.addComponent(id, spriteSheet);
        coordinator.addComponent(id, comp::ClientEntity());
        coordinator.addComponent(id, animationStates);

        return id;
    }

    exng::Entity createPlayer(exng::Coordinator& coordinator, exng::net::Packet& packet)
    {
        uint8_t playerNum;
        packet >> playerNum;

        auto id = coordinator.createEntity();

        auto hitboxID = createHitbox(coordinator);

        auto nameTagID = createNameTag(coordinator, sf::Color::Green, "Player " + std::to_string(playerNum));

        comp::Transform transform;
        transform.setPosition({100000.f, 0.f});
        transform.setScale({3.f, 3.f});
        transform.setRotation(0.f);
        transform.addChild(hitboxID, {0.f, 0.f}, true, true, false);
        transform.addChild(nameTagID, {0.f, -50.f}, true, false, false);

        comp::Drawable drawable;
        drawable.type = comp::Drawable::Type::SPRITE;
        drawable.sprite.shape.setTexture(exng::ResourceManager::getTexture("texture", "player_skins"));
        auto size = drawable.sprite.shape.getTexture()->getSize();
        auto width = size.x / 5;
        auto height = size.y / 5;
        drawable.sprite.shape.setTextureRect(sf::IntRect(width * 2, height * playerNum, size.x / 5, size.y / 5));

        comp::zIndex zIndex;
        zIndex.zIndex = 1;

        exng::effect::SpriteSheet animUp;
        exng::effect::SpriteSheet animIdle;
        exng::effect::SpriteSheet animDown;

        animUp.addFrame(exng::IntRect(width * 2, height * playerNum, width, height), 0.16f);
        animUp.addFrame(exng::IntRect(width * 3, height * playerNum, width, height), 0.16f);
        animUp.addFrame(exng::IntRect(width * 4, height * playerNum, width, height), 0.16f);
        animUp.setLoop(false);

        animIdle.addFrame(exng::IntRect(width * 2, height * playerNum, width, height), 0.16f);
        animIdle.setLoop(false);

        animDown.addFrame(exng::IntRect(width * 2, height * playerNum, width, height), 0.16f);
        animDown.addFrame(exng::IntRect(width * 1, height * playerNum, width, height), 0.16f);
        animDown.addFrame(exng::IntRect(width * 0, height * playerNum, width, height), 0.16f);
        animDown.setLoop(false);

        comp::SpriteSheet spriteSheet;
        spriteSheet.sheet = animIdle;

        comp::AnimationStates animationStates;
        animationStates.states.addState("idle", animIdle, false);
        animationStates.states.addState("up", animUp, true);
        animationStates.states.addState("down", animDown, true);
        animationStates.states.setState("idle", true);

        comp::OnDestruction onDestruction;
        onDestruction.callback = [&coordinator, id]() {
            auto position = coordinator.getComponent<comp::Transform>(id).getPosition();
            if (position.x + 100 < 0 || position.y + 100 < 0 || position.x > exng::context::getTargetResolution().x || position.y > exng::context::getTargetResolution().y)
                return;
            createLargeExplosion(coordinator, coordinator.getComponent<comp::Transform>(id).getPosition());
        };

        comp::Rigidbody rigidbody;

        coordinator.addComponent(id, transform);
        coordinator.addComponent(id, drawable);
        coordinator.addComponent(id, zIndex);
        coordinator.addComponent(id, spriteSheet);
        coordinator.addComponent(id, animationStates);
        coordinator.addComponent(id, comp::PlayerTag());
        coordinator.addComponent(id, rigidbody);
        coordinator.addComponent(id, onDestruction);
        return id;
    }

    exng::Entity createLaser(exng::Coordinator &coordinator, exng::net::Packet& packet)
    {
        auto id = coordinator.createEntity();

        auto hitboxID = createHitbox(coordinator);

        comp::Transform transform;
        transform.setPosition({100000.f, 0.f});
        transform.setScale({2.f, 2.f});
        transform.setRotation(0.f);
        transform.addChild(hitboxID, {0.f, 0.f}, true, true, false);

        comp::Drawable drawable;
        drawable.type = comp::Drawable::Type::RECTANGLE;
        drawable.rectangle.shape.setSize({10.f, 2.f});
        drawable.rectangle.shape.setFillColor(sf::Color::Red);

        comp::zIndex zIndex;
        zIndex.zIndex = 1;

        comp::Sound sound;
        sound.sound = std::make_shared<sf::Sound>();
        sound.sound->setBuffer(exng::ResourceManager::getSoundBuffer("sound", "laser"));
        sound.sound->setVolume(100.f);
        sound.sound->play();

        coordinator.addComponent(id, transform);
        coordinator.addComponent(id, drawable);
        coordinator.addComponent(id, zIndex);
        coordinator.addComponent(id, sound);

        return id;
    }

    exng::Entity createBatEnemy(exng::Coordinator &coordinator, exng::net::Packet& packet)
    {
        auto id = coordinator.createEntity();

        auto hitboxID = createHitbox(coordinator);

        comp::Transform transform;
        transform.setPosition(10000, 10000);
        transform.setScale({3.f, 3.f});
        transform.addChild(hitboxID, {0.f, 0.f}, true, true, false);

        comp::Drawable drawable;
        drawable.type = comp::Drawable::Type::SPRITE;
        drawable.sprite.shape.setTexture(exng::ResourceManager::getTexture("texture", "bat_enemy"));
        auto size = drawable.sprite.shape.getTexture()->getSize();
        auto width = size.x / 8;
        auto height = size.y;
        drawable.sprite.shape.setTextureRect(sf::IntRect(width * 7, 0, width, height));

        comp::SpriteSheet spriteSheet;
        for (int i = 0; i < 7; i++)
            spriteSheet.sheet.addFrame(exng::IntRect(width * i, 0, width, height), 0.16f);

        comp::AnimationStates animationStates;
        animationStates.states.addState("idle", spriteSheet.sheet, false);
        animationStates.states.setState("idle");

        spriteSheet.sheet.setLoop(true);

        comp::zIndex zIndex;
        zIndex.zIndex = 1;

        comp::OnDestruction onDestruction;
        onDestruction.callback = [&coordinator, id]() {
            auto position = coordinator.getComponent<comp::Transform>(id).getPosition();
            if (position.x + 100 < 0 || position.y + 100 < 0 || position.x > exng::context::getTargetResolution().x || position.y > exng::context::getTargetResolution().y)
                return;
            createLargeExplosion(coordinator, coordinator.getComponent<comp::Transform>(id).getPosition());
        };

        coordinator.addComponent(id, transform);
        coordinator.addComponent(id, drawable);
        coordinator.addComponent(id, zIndex);
        coordinator.addComponent(id, onDestruction);
        coordinator.addComponent(id, spriteSheet);
        coordinator.addComponent(id, animationStates);
        return id;
    }

    exng::Entity createObstacleBottom(exng::Coordinator &coordinator, exng::net::Packet& packet)
    {
        auto id = coordinator.createEntity();

        auto hitboxID = createHitbox(coordinator);

        comp::Transform transform;
        transform.setPosition(10000, 10000);
        transform.setScale({2.f, 2.f});
        transform.addChild(hitboxID, {0.f, 0.f}, true, true, false);

        comp::Drawable drawable;
        drawable.type = comp::Drawable::Type::SPRITE;
        drawable.sprite.shape.setTexture(exng::ResourceManager::getTexture("texture", "blocking_ground_ennemy"));
        auto size = drawable.sprite.shape.getTexture()->getSize();
        auto width = size.x / 8;
        auto height = size.y / 2;
        drawable.sprite.shape.setTextureRect(sf::IntRect(width * 7, 0, width, height));

        comp::SpriteSheet spriteSheet;
        for (int i = 0; i < 7; i++)
            spriteSheet.sheet.addFrame(exng::IntRect(width * i, 0, width, height), 0.16f);

        comp::AnimationStates animationStates;
        animationStates.states.addState("idle", spriteSheet.sheet, false);
        animationStates.states.setState("idle");

        spriteSheet.sheet.setLoop(true);

        comp::zIndex zIndex;
        zIndex.zIndex = 1;

        comp::OnDestruction onDestruction;
        onDestruction.callback = [&coordinator, id]() {
            auto position = coordinator.getComponent<comp::Transform>(id).getPosition();
            if (position.x + 100 < 0 || position.y + 100 < 0 || position.x > exng::context::getTargetResolution().x || position.y > exng::context::getTargetResolution().y)
                return;
            createLargeExplosion(coordinator, coordinator.getComponent<comp::Transform>(id).getPosition());
        };

        coordinator.addComponent(id, transform);
        coordinator.addComponent(id, drawable);
        coordinator.addComponent(id, zIndex);
        coordinator.addComponent(id, onDestruction);
        coordinator.addComponent(id, spriteSheet);
        coordinator.addComponent(id, animationStates);
        return id;
    }

    exng::Entity createObstacleTop(exng::Coordinator &coordinator, exng::net::Packet& packet)
    {
        auto id = coordinator.createEntity();

        auto hitboxID = createHitbox(coordinator);

        comp::Transform transform;
        transform.setPosition(10000, 10000);
        transform.setScale({2.f, 2.f});
        transform.addChild(hitboxID, {0.f, 0.f}, true, true, false);

        comp::Drawable drawable;
        drawable.type = comp::Drawable::Type::SPRITE;
        drawable.sprite.shape.setTexture(exng::ResourceManager::getTexture("texture", "blocking_ground_ennemy"));
        auto size = drawable.sprite.shape.getTexture()->getSize();
        auto width = size.x / 8;
        auto height = size.y / 2;
        drawable.sprite.shape.setTextureRect(sf::IntRect(width * 7, height, width, height));

        comp::SpriteSheet spriteSheet;
        for (int i = 0; i < 7; i++)
            spriteSheet.sheet.addFrame(exng::IntRect(width * i, height, width, height), 0.16f);

        comp::AnimationStates animationStates;
        animationStates.states.addState("idle", spriteSheet.sheet, false);
        animationStates.states.setState("idle");

        spriteSheet.sheet.setLoop(true);

        comp::zIndex zIndex;
        zIndex.zIndex = 1;

        comp::OnDestruction onDestruction;
        onDestruction.callback = [&coordinator, id]() {
            createLargeExplosion(coordinator, coordinator.getComponent<comp::Transform>(id).getPosition());
        };

        coordinator.addComponent(id, transform);
        coordinator.addComponent(id, drawable);
        coordinator.addComponent(id, zIndex);
        coordinator.addComponent(id, onDestruction);
        coordinator.addComponent(id, spriteSheet);
        coordinator.addComponent(id, animationStates);
        return id;
    }

    exng::Entity createSnake(exng::Coordinator &coordinator, exng::net::Packet& packet)
    {
        auto id = coordinator.createEntity();

        auto hitboxID = createHitbox(coordinator);

        comp::Transform transform;
        transform.setPosition(10000, 10000);
        transform.setScale({2.f, 2.f});
        transform.addChild(hitboxID, {0.f, 0.f}, true, true, false);

        comp::Drawable drawable;
        drawable.type = comp::Drawable::Type::SPRITE;
        drawable.sprite.shape.setTexture(exng::ResourceManager::getTexture("texture", "snake_head"));

        comp::zIndex zIndex;
        zIndex.zIndex = 1;

        comp::OnDestruction onDestruction;
        onDestruction.callback = [&coordinator, id]() {
            auto position = coordinator.getComponent<comp::Transform>(id).getPosition();
            if (position.x + 100 < 0 || position.y + 100 < 0 || position.x > exng::context::getTargetResolution().x || position.y > exng::context::getTargetResolution().y)
                return;
            createLargeExplosion(coordinator, coordinator.getComponent<comp::Transform>(id).getPosition());
        };

        coordinator.addComponent(id, transform);
        coordinator.addComponent(id, drawable);
        coordinator.addComponent(id, zIndex);
        coordinator.addComponent(id, onDestruction);
        return id;
    }

}