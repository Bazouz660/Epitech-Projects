/*
** EPITECH PROJECT, 2024
** B-CPP-500-STG-5-2-rtype-julian.lambert
** File description:
** SplashScreen
*/

#ifndef RTYPE_SCENE_SPLASHSCREEN_HPP
#define RTYPE_SCENE_SPLASHSCREEN_HPP

#include "core/scene/AScene.hpp"
#include "client/src/systems/systems.hpp"
#include "core/net/UDPClient.hpp"
#include "core/effects/Fade.hpp"

namespace rtype::scene {
    class SplashScreen : public exng::AScene {
        public:
            SplashScreen(exng::net::UDPClient &UDPclient, exng::SceneManager& sceneManager);
            ~SplashScreen() override;

            void processEvents(sf::Event& event) override;
            void update(float dt) override;
            void render(exng::Window& target) override;

            void onEnter() override;
            void onExit() override;

        private:
            sf::Sprite m_logo;
            sf::CircleShape m_loadingCircle;
            exng::effect::Fade m_fade;
            exng::net::UDPClient &m_udpClient;
            float m_loadingTimer = 0.f;
            float m_loadingMinTime = 2.f;

            float m_delayedTimer = 0.f;
    };
}

#endif // !RTYPE_SCENE_SPLASHSCREEN_HPP