/*
** EPITECH PROJECT, 2024
** B-CPP-500-STG-5-2-rtype-julian.lambert
** File description:
** Game
*/

#ifndef RTYPE_SCENE_GAME_HPP
#define RTYPE_SCENE_GAME_HPP

#include "client/src/EntityFactory.hpp"

#include "ANetScene.hpp"
#include "client/src/systems/systems.hpp"
#include "helper/SafeDequeue.hpp"
#include "core/gui/LayerBackground.hpp"
#include "core/gui/Container.hpp"

#include <queue>
#include <atomic>
#include "helper/SafeUnorderedMap.hpp"

namespace rtype::scene {
    class Game : public ANetScene {
        public:
            Game(exng::net::UDPClient &UDPclient, exng::SceneManager& sceneManager, exng::Entity m_playerServerId);
            ~Game() override = default;

            void processEvents(sf::Event& event) override;
            void update(float dt) override;
            void render(exng::Window& target) override;

            // packet handlers
            void handlePing(exng::net::Packet &packet, exng::net::UDPClient &client);

            void handleServerStopped(exng::net::Packet &packet, exng::net::UDPClient &client);

            void handleNewEntity(exng::net::Packet &packet, exng::net::UDPClient &client);
            void handleEntityPositionUpdate(exng::net::Packet &packet, exng::net::UDPClient &client);
            void handleDisconnection(exng::net::Packet &packet, exng::net::UDPClient &client);
            void handleEntityDestroyed(exng::net::Packet &packet, exng::net::UDPClient &client);
            void handleHitboxUpdate(exng::net::Packet &packet, exng::net::UDPClient &client);
            void handlePlayerInfo(exng::net::Packet &packet, exng::net::UDPClient &client);

            void onEnter() override;
            void onExit() override;

        private:
            void createGUI();
            void createGameOverGUI();

            // leaves the server and goes back to the main menu
            void backToMenu();

            // health of the local player, fed by the PlayerInfo packets.
            // maxHp starts at 1 so that the life bar ratio is never a division
            // by zero before the first packet arrives.
            std::atomic<int> m_playerHp = 0;
            std::atomic<int> m_playerMaxHp = 1;

            std::shared_ptr<sys::UpdateTransform> m_transformSystem;
            std::shared_ptr<sys::RenderSystem> m_renderSystem;
            std::shared_ptr<sys::UpdateAABB> m_aabbSystem;
            std::shared_ptr<sys::SpriteSheetSystem> m_spriteSheetSystem;
            std::shared_ptr<sys::AnimationStatesSystem> m_animationStatesSystem;

            exng::SafeDequeue<std::pair<exng::Entity, bool>> m_entitiesToDestroy;

            exng::SafeUnorderedMap<exng::Entity, exng::Entity> m_clientToServerEntities;

            exng::gui::Container m_guiContainer;
            exng::gui::Container m_gameOverContainer;

            // reason shown on the end screen
            std::atomic<bool> m_serverStopped = false;

            exng::gui::LayerBackground m_background;

            exng::gui::LayerBackground m_foreground;

            EntityFactory m_entityFactory;

            std::unique_ptr<exng::Entity> m_playerClientId = nullptr;

            std::atomic<bool> m_alive = true;
    };
}

#endif // !RTYPE_SCENE_GAME_HPP