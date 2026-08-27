/*
** EPITECH PROJECT, 2024
** B-CPP-500-STG-5-2-rtype-julian.lambert
** File description:
** ARTypeScene
*/

#ifndef RTYPE_ANETSCENE_HPP
#define RTYPE_ANETSCENE_HPP

#include "core/scene/AScene.hpp"
#include "core/event/Keyboard.hpp"
#include "core/net/Packet.hpp"
#include "core/net/UDPClient.hpp"
#include "core/ecs/coordinator.hpp"
#include "core/scene/SceneManager.hpp"

#include "shared/include/protocol.h"

#include <unordered_map>
#include <map>

namespace rtype {

    class ANetScene : public exng::AScene {
        public:
            ANetScene(exng::net::UDPClient &UDPclient, exng::SceneManager& sceneManager)
                : AScene(sceneManager), m_UDPclient(UDPclient)
            {
            }

            ~ANetScene() override = default;

            void registerNetKeyEvent(exng::Keyboard::Key key)
            {
                m_keyStates[key] = false;
            }

            void processNetKeyEvents(sf::Event &event)
            {
                if (event.type == sf::Event::KeyPressed) {
                    auto key = static_cast<exng::Keyboard::Key>(event.key.code);
                    auto found = m_keyStates.find(key) != m_keyStates.end();
                    if (!found) {
                        return;
                    }

                    bool pressed = m_keyStates[key];
                    if (found && !pressed && m_UDPclient.isConnected()) {
                        sendNetKeyEvent(key, true);
                    }
                }
                else if (event.type == sf::Event::KeyReleased) {
                    auto key = static_cast<exng::Keyboard::Key>(event.key.code);
                    auto found = m_keyStates.find(key) != m_keyStates.end();
                    if (!found) {
                        return;
                    }
                    bool pressed = m_keyStates[key];
                    if (found && pressed && m_UDPclient.isConnected())
                        sendNetKeyEvent(key, false);
                }
            }

        private:
            void sendNetKeyEvent(exng::Keyboard::Key key, bool isPressed) {
                m_keyStates[key] = isPressed;
                exng::net::Packet packet(rtype::MessageType::Input);
                packet << m_playerServerId;
                packet << key;
                packet << isPressed;
                m_UDPclient.reliableSend(packet);
            }

        protected:
            std::unordered_map<exng::Keyboard::Key, bool> m_keyStates;
            exng::net::UDPClient &m_UDPclient;

            exng::Entity m_playerServerId;
    };
}

#endif // !RTYPE_ANETSCENE_HPP