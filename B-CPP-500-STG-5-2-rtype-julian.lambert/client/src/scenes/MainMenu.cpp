/*
** EPITECH PROJECT, 2024
** B-CPP-500-STG-5-2-rtype-julian.lambert
** File description:
** MainMenu
*/

#include "Game.hpp"     // game scene
#include "MainMenu.hpp" // main menu scene

// engine includes
#include "core/ecs/coordinator.hpp"
#include "core/event/Keyboard.hpp"
#include "core/resource_manager/ResourceManager.hpp"
#include "core/resource_manager/music_manager/MusicManager.hpp"
#include "core/gui/Button.hpp"
#include "core/gui/InputBox.hpp"
#include "core/gui/Label.hpp"
#include "core/gui/ProgressBar.hpp"
#include "core/gui/Image.hpp"
#include "helper/info/context.hpp"

namespace rtype::scene
{
    MainMenu::MainMenu(exng::net::UDPClient &UDPclient, exng::SceneManager &sceneManager)
        : ANetScene(UDPclient, sceneManager)
    {
    }

    MainMenu::~MainMenu()
    {
    }

    void MainMenu::onEnter()
    {
        exng::MusicManager::switchTrack("doigbite", 5, true, true);
        createGUI();

        m_UDPclient.registerPacketHandler(rtype::MessageType::ConnectionRefused,
                                          [this](exng::net::Packet &packet, exng::net::UDPClient &client)
                                          {
                                              this->handleConnectionRefused(packet, client);
                                          });

        m_UDPclient.registerPacketHandler(rtype::MessageType::ConnectionAccepted,
                                          [this](exng::net::Packet &packet, exng::net::UDPClient &client)
                                          {
                                              this->handleConnectionAccepted(packet, client);
                                          });
    }

    void MainMenu::onExit()
    {
        exng::MusicManager::pauseTrack(0.5);

        m_UDPclient.unregisterPacketHandler(rtype::MessageType::ConnectionRefused);
        m_UDPclient.unregisterPacketHandler(rtype::MessageType::ConnectionAccepted);
    }

    void MainMenu::createGUI()
    {
        sf::Vector2f res = sf::Vector2f(exng::context::getTargetResolution().x, exng::context::getTargetResolution().y);

        m_background.addLayer(
            exng::Vector2f(res.x, res.y),
            exng::Vector2f(0, 0),
            exng::ResourceManager::getTexture("background", "stage1"),
            exng::Vector2f(5, 0));

        m_background.addLayer(
            exng::Vector2f(res.x, res.y),
            exng::Vector2f(0, 0),
            exng::ResourceManager::getTexture("background", "StarsSmall"),
            exng::Vector2f(10, 0));

        m_background.addLayer(
            exng::Vector2f(res.x, res.y),
            exng::Vector2f(0, 0),
            exng::ResourceManager::getTexture("background", "StarsBig_2"),
            exng::Vector2f(12, 0));

        m_background.addLayer(
            exng::Vector2f(res.x, res.y),
            exng::Vector2f(0, 0),
            exng::ResourceManager::getTexture("background", "StarsBig_1"),
            exng::Vector2f(15, 0));

        {
            auto title = std::make_shared<exng::gui::Image>(
                exng::ResourceManager::getTexture("gui", "R-Type_Logo"),
                sf::Vector2f(res.x / 2, res.y / 4));

            title->getShape().setScale(4.f, 4.f);

            auto ipInput = std::make_shared<exng::gui::InputBox>(
                sf::Vector2f(200, 50),
                sf::Vector2f(res.x / 2, res.y / 2 + 60),
                "IP");

            auto portInput = std::make_shared<exng::gui::InputBox>(
                sf::Vector2f(200, 50),
                sf::Vector2f(res.x / 2, res.y / 2 + 120),
                "Port");

            m_guiContainer.addComponent(title);
            m_guiContainer.addComponent(ipInput);
            m_guiContainer.addComponent(portInput);
        }

        auto playButton = std::make_shared<exng::gui::Button>(
            sf::Vector2f(200, 50),
            sf::Vector2f(res.x / 2, res.y / 2 + 180),
            "Play",
            [this]() {
                auto ipInput = m_guiContainer.getComponent<exng::gui::InputBox>(1);
                auto portInput = m_guiContainer.getComponent<exng::gui::InputBox>(2);

                std::string ip = ipInput->getInputString();
                std::string port = portInput->getInputString();

                if (ip.empty() || port.empty())
                    return;

                m_UDPclient.connect(ip, std::stoi(port), MessageType::ConnectionRequest);
                m_waitingForConnection = true;
            });

        auto settingsButton = std::make_shared<exng::gui::Button>(
            sf::Vector2f(200, 50),
            sf::Vector2f(res.x / 2, res.y / 2 + 240),
            "Settings",
            [this]() {});
        
        auto quitButton = std::make_shared<exng::gui::Button>(
            sf::Vector2f(200, 50),
            sf::Vector2f(res.x / 2, res.y / 2 + 300),
            "Quit",
            [this]() {});
        
        m_guiContainer.addComponent(playButton);
        m_guiContainer.addComponent(settingsButton);
        m_guiContainer.addComponent(quitButton);
    }

    void MainMenu::processEvents(sf::Event &event)
    {
        processNetKeyEvents(event);

        m_guiContainer.handleEvent(event);
    }

    void MainMenu::update(float dt)
    {
        if (m_UDPclient.isConnected())
        {

            exng::logger::success() << "Connected to server";

            if (!m_sceneManager.isSceneLoaded("Game"))
                m_sceneManager.loadScene("Game", std::make_shared<scene::Game>(m_UDPclient, m_sceneManager, m_playerServerId));
            m_sceneManager.switchScene("Game");
        }

        if (m_waitingForConnection)
        {
            m_connectionTimer += dt;
            if (m_connectionTimer >= m_connectionTimeout)
            {
                m_waitingForConnection = false;
                m_connectionTimer = 0.f;
                exng::logger::error() << "Connection timed out";
            }
        }

        m_guiContainer.update();
        m_background.update(dt);
    }

    void MainMenu::render(exng::Window &target)
    {
        m_background.render(target);
        m_guiContainer.render(target);
    }
}
