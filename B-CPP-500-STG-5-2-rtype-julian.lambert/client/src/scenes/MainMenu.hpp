/*
** EPITECH PROJECT, 2024
** B-CPP-500-STG-5-2-rtype-julian.lambert
** File description:
** MainMenu
*/

#ifndef RTYPE_SCENE_MAINMENU_HPP
#define RTYPE_SCENE_MAINMENU_HPP

#include "ANetScene.hpp"
#include "client/src/systems/systems.hpp"

#include "core/gui/Container.hpp"
#include "core/gui/LayerBackground.hpp"

namespace rtype::scene {
    class MainMenu : public ANetScene {
        public:
            MainMenu(exng::net::UDPClient &UDPclient, exng::SceneManager& sceneManager);
            ~MainMenu() override;

            void processEvents(sf::Event& event) override;
            void update(float dt) override;
            void render(exng::Window& target) override;

            // packet handlers
            void handleConnectionAccepted(exng::net::Packet &packet, exng::net::UDPClient &client);
            void handleConnectionRefused(exng::net::Packet &packet, exng::net::UDPClient &client);

            void onEnter() override;
            void onExit() override;

        private:
            void createGUI();

            float m_connectionTimeout = 5.f;
            float m_connectionTimer = 0.f;
            bool m_waitingForConnection = false;

            exng::gui::Container m_guiContainer;
            exng::gui::LayerBackground m_background;
    };
}

#endif // !RTYPE_SCENE_MAINMENU_HPP