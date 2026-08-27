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

#include <atomic>

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
            // What the status line under the buttons currently shows. Set from
            // the network thread, read from the game thread, hence the atomic.
            enum class Status {
                Idle,
                Connecting,
                Refused,
                TimedOut,
                BadAddress,
                BadPort
            };

            void createGUI();
            void createSettingsGUI();

            // starts a connection attempt from the content of the input boxes
            void onPlayClicked();

            void refreshStatusLabel();
            void refreshVolumeLabel();

            float m_connectionTimeout = 5.f;
            float m_connectionTimer = 0.f;
            bool m_waitingForConnection = false;

            std::atomic<Status> m_status = Status::Idle;
            Status m_displayedStatus = Status::Idle;

            bool m_settingsOpen = false;
            float m_musicVolume = 100.f;

            exng::gui::Container m_guiContainer;
            exng::gui::Container m_settingsContainer;
            exng::gui::LayerBackground m_background;
    };
}

#endif // !RTYPE_SCENE_MAINMENU_HPP
