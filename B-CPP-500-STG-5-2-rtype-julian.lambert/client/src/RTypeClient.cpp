/*
** EPITECH PROJECT, 2023
** B-CPP-500-STG-5-2-rtype-julian.lambert
** File description:
** RTypeClient
*/

#include "RTypeClient.hpp"
#include "scenes/Game.hpp"
#include "scenes/MainMenu.hpp"
#include "scenes/SplashScreen.hpp"
#include "core/resource_manager/ResourceManager.hpp"
#include "helper/info/context.hpp"
#include "helper/paths.hpp"

namespace rtype {

    RTypeClient::RTypeClient()
    {
        exng::context::setTargetResolution(1920, 1080);

        exng::ResourceManager::loadResource(exng::ResourceType::Texture, "asset/icon/youpiLogo.png");
        exng::ResourceManager::loadResource(exng::ResourceType::Texture, "asset/icon/loading.png");

        while (exng::ResourceManager::isLoading()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }

        m_sceneManager.registerScene("SplashScreen");
        m_sceneManager.registerScene("MainMenu");
        m_sceneManager.registerScene("Game");
        m_sceneManager.loadScene("SplashScreen", std::make_shared<scene::SplashScreen>(m_UDPclient, m_sceneManager));
        m_sceneManager.switchScene("SplashScreen");
    }

    RTypeClient::~RTypeClient()
    {
        exng::ResourceManager::stop();
    }

    void RTypeClient::run()
    {
        runNetwork();
        runGame();
    }

    void RTypeClient::runNetwork()
    {
        m_netClientThread = std::thread([this]() {

            exng::Chrono chrono;

            while (!m_shouldClose || m_UDPclient.isConnected()) {

                chrono.update();

                m_UDPclient.handleIncomingData();

                if (m_tickTimer >= m_tickRate) {
                    m_tickTimer = 0.f;
                    m_UDPclient.handleOutgoingData();
                }

                if (m_shouldClose) {
                    m_disconnectionTimer += chrono.getFrameDt().asSeconds();
                    if (m_disconnectionTimer >= m_disconnectionTimeout) {
                        m_UDPclient.setConnected(false);
                    }
                }

                m_tickTimer += chrono.getFrameDt().asSeconds();

                // the socket is non blocking: without this the thread would
                // spin at 100% of a core for nothing
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }

            exng::logger::log() << "Closing network thread";
        });
    }

    void RTypeClient::runGame()
    {
        m_window.create("R-Type", exng::context::getTargetResolution(), false);
        m_window.setIcon(exng::paths::resolve("asset/icon/youpiLogo.png"));
        m_window.setFramerateLimit(60);

        while (m_window.isOpen() && !m_shouldClose) {

            // update clocks
            m_logicChrono.update();

            // process events
            while (m_window.pollEvent(m_event)) {
                if (m_event.type == sf::Event::Closed) {
                    requestClose();
                    break;
                }

                if (m_event.type == sf::Event::KeyPressed && m_event.key.code == sf::Keyboard::F11) {
                    m_window.setFullscreen(!m_window.isFullscreen());
                    continue;
                }

                // the window is not necessarily the size the game draws at:
                // bring mouse coordinates back into the game referential so
                // that the GUI hit tests stay correct
                remapMouseCoordinates(m_event);

                m_sceneManager.getCurrentScene()->processEvents(m_event);
            }

            if (exng::context::consumeFullscreenToggle())
                m_window.setFullscreen(!m_window.isFullscreen());

            if (exng::context::isQuitRequested())
                requestClose();

            if (!m_window.isOpen() || m_shouldClose)
                break;

            // update
            m_sceneManager.getCurrentScene()->update(m_logicChrono.getFrameDt().asSeconds());

            // check if we can draw
            if (!m_window.isOpen())
                break;

            // draw
            m_window.clear();
            m_sceneManager.getCurrentScene()->render(m_window);
            m_window.display();
        }

        if (m_netClientThread.joinable())
            m_netClientThread.join();

        exng::logger::log() << "Closing window";
    }

    void RTypeClient::requestClose()
    {
        if (m_shouldClose)
            return;

        m_UDPclient.disconnect(rtype::MessageType::DisconnectionRequest);
        m_shouldClose = true;
        m_window.close();
    }

    void RTypeClient::remapMouseCoordinates(sf::Event &event)
    {
        switch (event.type) {
            case sf::Event::MouseMoved: {
                auto coords = m_window.mapPixelToCoords(event.mouseMove.x, event.mouseMove.y);
                event.mouseMove.x = static_cast<int>(coords.x);
                event.mouseMove.y = static_cast<int>(coords.y);
                break;
            }
            case sf::Event::MouseButtonPressed:
            case sf::Event::MouseButtonReleased: {
                auto coords = m_window.mapPixelToCoords(event.mouseButton.x, event.mouseButton.y);
                event.mouseButton.x = static_cast<int>(coords.x);
                event.mouseButton.y = static_cast<int>(coords.y);
                break;
            }
            case sf::Event::MouseWheelScrolled: {
                auto coords = m_window.mapPixelToCoords(event.mouseWheelScroll.x, event.mouseWheelScroll.y);
                event.mouseWheelScroll.x = static_cast<int>(coords.x);
                event.mouseWheelScroll.y = static_cast<int>(coords.y);
                break;
            }
            default:
                break;
        }
    }

}