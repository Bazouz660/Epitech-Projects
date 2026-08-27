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

            float pingTimer = 0;
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
            }

            exng::logger::log() << "Closing network thread";
        });
    }

    void RTypeClient::runGame()
    {
        m_window.create("Rtype", exng::context::getTargetResolution(), false);
        m_window.setFramerateLimit(60);

        while (m_window.isOpen() && !m_shouldClose) {

            // update clocks
            m_logicChrono.update();

            // process events
            while (m_window.pollEvent(m_event)) {
                if (m_event.type == sf::Event::Closed) {
                    m_window.close();
                    m_UDPclient.disconnect(rtype::MessageType::DisconnectionRequest);
                    m_shouldClose = true;
                }

                m_sceneManager.getCurrentScene()->processEvents(m_event);
            }

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

}