/*
** EPITECH PROJECT, 2024
** B-CPP-500-STG-5-2-rtype-julian.lambert
** File description:
** Game
*/

#include "Game.hpp"
#include "core/ecs/coordinator.hpp"
#include "core/event/Keyboard.hpp"
#include "core/resource_manager/music_manager/MusicManager.hpp"
#include "core/resource_manager/ResourceManager.hpp"
#include "core/gui/ProgressBar.hpp"
#include "core/gui/Button.hpp"
#include "core/gui/Label.hpp"
#include "helper/info/context.hpp"

#include "client/src/entityConstructors.hpp"

namespace rtype::scene {

    Game::Game(exng::net::UDPClient &UDPclient, exng::SceneManager& sceneManager, exng::Entity playerServerId)
        : ANetScene(UDPclient, sceneManager)
    {
        m_playerServerId = playerServerId;

        m_coordinator.registerComponent<comp::AnimationStates>();
        m_coordinator.registerComponent<comp::OnDestruction>();
        m_coordinator.registerComponent<comp::ClientEntity>();
        m_coordinator.registerComponent<comp::ServerEntity>();
        m_coordinator.registerComponent<comp::SpriteSheet>();
        m_coordinator.registerComponent<comp::Rigidbody>();
        m_coordinator.registerComponent<comp::PlayerTag>();
        m_coordinator.registerComponent<comp::Transform>();
        m_coordinator.registerComponent<comp::Drawable>();
        m_coordinator.registerComponent<comp::zIndex>();
        m_coordinator.registerComponent<comp::Sound>();
        m_coordinator.registerComponent<comp::AABB>();

        m_transformSystem = m_coordinator.createSystem<sys::UpdateTransform,
            comp::Transform
        >();

        m_renderSystem = m_coordinator.createSystem<sys::RenderSystem,
            comp::Transform,
            comp::Drawable
        >();

        m_aabbSystem = m_coordinator.createSystem<sys::UpdateAABB,
            comp::Transform,
            comp::AABB
        >();

        m_spriteSheetSystem = m_coordinator.createSystem<sys::SpriteSheetSystem,
            comp::SpriteSheet,
            comp::Drawable
        >();

        m_animationStatesSystem = m_coordinator.createSystem<sys::AnimationStatesSystem,
            comp::AnimationStates
        >();

        m_keyStates[exng::Keyboard::Key::Up] = false;
        m_keyStates[exng::Keyboard::Key::Down] = false;
        m_keyStates[exng::Keyboard::Key::Left] = false;
        m_keyStates[exng::Keyboard::Key::Right] = false;
        m_keyStates[exng::Keyboard::Key::Space] = false;

        m_entityFactory.registerConstructor(EntityType::Player, constructors::createPlayer);
        m_entityFactory.registerConstructor(EntityType::Laser, constructors::createLaser);
        m_entityFactory.registerConstructor(EntityType::BatEnemy, constructors::createBatEnemy);
        m_entityFactory.registerConstructor(EntityType::Obstacle_top, constructors::createObstacleTop);
        m_entityFactory.registerConstructor(EntityType::Obstacle_bottom, constructors::createObstacleBottom);
        m_entityFactory.registerConstructor(EntityType::Snake, constructors::createSnake);

        createGUI();
        createGameOverGUI();
    }

    void Game::onEnter()
    {
        exng::MusicManager::switchTrack("stage1", 1, true, true);
        exng::MusicManager::setVolume(50);

        auto res = exng::context::getTargetResolution();

        m_background.addLayer(
            exng::Vector2f(res.x, res.y),
            exng::Vector2f(0, 0),
            exng::ResourceManager::getTexture("background", "stage1"),
            exng::Vector2f(50, 0)
        );

        m_background.addLayer(
            exng::Vector2f(res.x, res.y),
            exng::Vector2f(0, 0),
            exng::ResourceManager::getTexture("background", "StarsSmall"),
            exng::Vector2f(60, 0)
        );

        m_background.addLayer(
            exng::Vector2f(res.x, res.y),
            exng::Vector2f(0, 0),
            exng::ResourceManager::getTexture("background", "StarsBig_2"),
            exng::Vector2f(70, 0)
        );

        m_background.addLayer(
            exng::Vector2f(res.x, res.y),
            exng::Vector2f(0, 0),
            exng::ResourceManager::getTexture("background", "StarsBig_1"),
            exng::Vector2f(80, 0)
        );

        m_foreground.addLayer(
            exng::Vector2f(7231.30434782, res.y),
            exng::Vector2f(0, 0),
            exng::ResourceManager::getTexture("background", "decor"),
            exng::Vector2f(15, 0)
        );

        m_UDPclient.registerPacketHandler(rtype::MessageType::NewEntity,
            [this](exng::net::Packet &packet, exng::net::UDPClient &client) {
                this->handleNewEntity(packet, client);
            }
        );

        m_UDPclient.registerPacketHandler(rtype::MessageType::Ping,
            [this](exng::net::Packet &packet, exng::net::UDPClient &client) {
                this->handlePing(packet, client);
            }
        );

        m_UDPclient.registerPacketHandler(rtype::MessageType::ServerStopped,
            [this](exng::net::Packet &packet, exng::net::UDPClient &client) {
                this->handleServerStopped(packet, client);
            }
        );

        m_UDPclient.registerPacketHandler(rtype::MessageType::EntityPositionUpdate,
            [this](exng::net::Packet &packet, exng::net::UDPClient &client) {
                this->handleEntityPositionUpdate(packet, client);
            }
        );

        m_UDPclient.registerPacketHandler(rtype::MessageType::Disconnection,
            [this](exng::net::Packet &packet, exng::net::UDPClient &client) {
                this->handleDisconnection(packet, client);
            }
        );

        m_UDPclient.registerPacketHandler(rtype::MessageType::EntityDestroyed,
            [this](exng::net::Packet &packet, exng::net::UDPClient &client) {
                this->handleEntityDestroyed(packet, client);
            }
        );

        m_UDPclient.registerPacketHandler(rtype::MessageType::EntityHitboxUpdate,
            [this](exng::net::Packet &packet, exng::net::UDPClient &client) {
                this->handleHitboxUpdate(packet, client);
            }
        );

        m_UDPclient.registerPacketHandler(rtype::MessageType::PlayerInfo,
            [this](exng::net::Packet &packet, exng::net::UDPClient &client) {
                this->handlePlayerInfo(packet, client);
            }
        );
    }

    void Game::onExit()
    {
        exng::MusicManager::pauseTrack(0.5);

        m_UDPclient.unregisterPacketHandler(rtype::MessageType::NewEntity);
        m_UDPclient.unregisterPacketHandler(rtype::MessageType::Ping);
        m_UDPclient.unregisterPacketHandler(rtype::MessageType::ServerStopped);
        m_UDPclient.unregisterPacketHandler(rtype::MessageType::EntityPositionUpdate);
        m_UDPclient.unregisterPacketHandler(rtype::MessageType::Disconnection);
        m_UDPclient.unregisterPacketHandler(rtype::MessageType::EntityDestroyed);
        m_UDPclient.unregisterPacketHandler(rtype::MessageType::EntityHitboxUpdate);
        m_UDPclient.unregisterPacketHandler(rtype::MessageType::PlayerInfo);
    }

    void Game::createGUI()
    {
        auto lifebar = std::make_shared<exng::gui::ProgressBar>(
            sf::Vector2f(300, 50),
            sf::Vector2f(50, 50)
        );
        lifebar->getShape().setTexture(&exng::ResourceManager::getTexture("gui", "lifebar_empty"));
        lifebar->getBar().setTexture(&exng::ResourceManager::getTexture("gui", "lifebar_filled"));

        m_guiContainer.addComponent(lifebar);
    }

    void Game::createGameOverGUI()
    {
        auto res = exng::context::getTargetResolution();

        auto title = std::make_shared<exng::gui::Label>(
            sf::Vector2f(res.x / 2.f, res.y / 2.f - 120.f),
            "GAME OVER",
            72);
        title->getText().setFillColor(sf::Color(230, 90, 90));
        title->centerOrigin();

        auto backButton = std::make_shared<exng::gui::Button>(
            sf::Vector2f(300, 50),
            sf::Vector2f(res.x / 2.f, res.y / 2.f + 40.f),
            "Back to menu",
            [this]() { this->backToMenu(); });

        auto quitButton = std::make_shared<exng::gui::Button>(
            sf::Vector2f(300, 50),
            sf::Vector2f(res.x / 2.f, res.y / 2.f + 110.f),
            "Quit",
            []() { exng::context::requestQuit(); });

        m_gameOverContainer.addComponent(title);
        m_gameOverContainer.addComponent(backButton);
        m_gameOverContainer.addComponent(quitButton);
    }

    void Game::backToMenu()
    {
        // tell the server we are leaving, then let the menu take over: the
        // packet is flushed by the network thread on its next tick
        if (m_UDPclient.isConnected())
            m_UDPclient.disconnect(rtype::MessageType::DisconnectionRequest);
        m_UDPclient.setConnected(false);

        m_sceneManager.switchScene("MainMenu");
    }

    void Game::processEvents(sf::Event& event)
    {
        if (m_alive) {
            processNetKeyEvents(event);
            m_guiContainer.handleEvent(event);
        } else {
            m_gameOverContainer.handleEvent(event);
        }
    }

    void Game::update(float dt)
    {
        // the server went away while we were playing: same end screen
        if (m_serverStopped)
            m_alive = false;

        m_background.update(dt);
        m_foreground.update(dt);

        if (m_alive) {
            int maxHp = m_playerMaxHp;
            m_guiContainer.getComponent<exng::gui::ProgressBar>(0)->setProgress(
                maxHp > 0 ? static_cast<float>(m_playerHp) / static_cast<float>(maxHp) : 0.f
            );
            m_guiContainer.update();
        } else {
            m_gameOverContainer.update();
        }

        // the world keeps being simulated once we are dead: entities the
        // server destroys still have to be reaped, otherwise the coordinator
        // would fill up while the end screen is shown

        m_transformSystem->update();
        m_aabbSystem->update();
        m_spriteSheetSystem->update(dt, m_entitiesToDestroy);
        m_animationStatesSystem->update(dt);

        while (!m_entitiesToDestroy.empty()) {
            exng::Entity id = m_entitiesToDestroy.front().first;
            bool clientSideEntity = m_entitiesToDestroy.front().second;
            m_entitiesToDestroy.pop();

            exng::Entity entityId;
            if (clientSideEntity) {
                entityId = id;
            } else {
                try {
                    entityId = m_clientToServerEntities.at(id);
                } catch (std::exception &e) {
                    exng::logger::warn() << "Received destruction for unknown entity " << id;
                    continue; // one unknown id must not stall the rest of the queue
                }
            }

            if (m_coordinator.hasComponent<comp::Transform>(entityId)) {
                auto children = m_coordinator.getComponent<comp::Transform>(entityId).getChildren();
                for (auto &child : children) {
                    m_coordinator.destroyEntity(child.entity);
                }
            }

            if (m_coordinator.hasComponent<comp::OnDestruction>(entityId)) {
                auto &onDestruction = m_coordinator.getComponent<comp::OnDestruction>(entityId);
                onDestruction.callback();
            }

            if (clientSideEntity)
                m_coordinator.destroyEntity(entityId);
            else {
                m_clientToServerEntities.erase(id);
                m_coordinator.destroyEntity(entityId);

                if (m_playerClientId && entityId == *m_playerClientId) {
                    m_alive = false;
                    exng::logger::log() << "Unalived player";
                }
            }
        }
    }

    void Game::render(exng::Window& target)
    {
        m_background.render(target);
        //m_foreground.render(target);
        m_renderSystem->render(target);

        if (m_alive)
            m_guiContainer.render(target);
        else
            m_gameOverContainer.render(target);
    }
}
