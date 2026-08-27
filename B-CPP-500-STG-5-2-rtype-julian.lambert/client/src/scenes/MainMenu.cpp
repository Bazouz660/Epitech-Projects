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

#include <algorithm>

namespace rtype::scene
{
    namespace {
        // Index of every component inside m_guiContainer / m_settingsContainer.
        // Container only exposes components by position, so keeping the
        // indices named here avoids magic numbers spread over the file.
        enum MenuItem {
            Title = 0,
            IpInput,
            PortInput,
            PlayButton,
            SettingsButton,
            QuitButton,
            StatusLabel
        };

        enum SettingsItem {
            SettingsTitle = 0,
            VolumeLabel,
            VolumeBar,
            VolumeDown,
            VolumeUp,
            FullscreenButton,
            BackButton
        };

        constexpr const char *DEFAULT_IP = "127.0.0.1";
        constexpr const char *DEFAULT_PORT = "4040";
    }

    MainMenu::MainMenu(exng::net::UDPClient &UDPclient, exng::SceneManager &sceneManager)
        : ANetScene(UDPclient, sceneManager)
    {
        // built once: onEnter runs again every time we come back from a game,
        // and the containers have no way to drop their components
        createGUI();
        createSettingsGUI();
    }

    MainMenu::~MainMenu()
    {
    }

    void MainMenu::onEnter()
    {
        exng::MusicManager::switchTrack("doigbite", 5, true, true);

        // Coming back from a finished game: drop the old scene so that the
        // next connection starts from a clean state.
        if (m_sceneManager.isSceneLoaded("Game"))
            m_sceneManager.unloadScene("Game");

        m_waitingForConnection = false;
        m_connectionTimer = 0.f;
        m_settingsOpen = false;
        m_status = Status::Idle;
        m_displayedStatus = Status::Idle;

        refreshStatusLabel();

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

            // Playing on the same machine is by far the most common case:
            // start from something that just works instead of an empty box.
            ipInput->setInputString(DEFAULT_IP);
            portInput->setInputString(DEFAULT_PORT);

            m_guiContainer.addComponent(title);
            m_guiContainer.addComponent(ipInput);
            m_guiContainer.addComponent(portInput);
        }

        auto playButton = std::make_shared<exng::gui::Button>(
            sf::Vector2f(200, 50),
            sf::Vector2f(res.x / 2, res.y / 2 + 180),
            "Play",
            [this]() { this->onPlayClicked(); });

        auto settingsButton = std::make_shared<exng::gui::Button>(
            sf::Vector2f(200, 50),
            sf::Vector2f(res.x / 2, res.y / 2 + 240),
            "Settings",
            [this]() { m_settingsOpen = true; });

        auto quitButton = std::make_shared<exng::gui::Button>(
            sf::Vector2f(200, 50),
            sf::Vector2f(res.x / 2, res.y / 2 + 300),
            "Quit",
            []() { exng::context::requestQuit(); });

        auto statusLabel = std::make_shared<exng::gui::Label>(
            sf::Vector2f(res.x / 2, res.y / 2 + 370),
            "",
            26);

        m_guiContainer.addComponent(playButton);
        m_guiContainer.addComponent(settingsButton);
        m_guiContainer.addComponent(quitButton);
        m_guiContainer.addComponent(statusLabel);
    }

    void MainMenu::createSettingsGUI()
    {
        sf::Vector2f res = sf::Vector2f(exng::context::getTargetResolution().x, exng::context::getTargetResolution().y);

        m_musicVolume = exng::MusicManager::getMusicVolume();

        auto title = std::make_shared<exng::gui::Label>(
            sf::Vector2f(res.x / 2, res.y / 3),
            "Settings",
            48);
        title->centerOrigin();

        auto volumeLabel = std::make_shared<exng::gui::Label>(
            sf::Vector2f(res.x / 2, res.y / 2 - 40),
            "Music",
            30);
        volumeLabel->centerOrigin();

        auto volumeBar = std::make_shared<exng::gui::ProgressBar>(
            sf::Vector2f(300, 30),
            sf::Vector2f(res.x / 2 - 150, res.y / 2));
        volumeBar->getShape().setFillColor(sf::Color(30, 30, 30));
        volumeBar->getBar().setFillColor(sf::Color(80, 200, 120));
        volumeBar->setProgress(m_musicVolume / 100.f);

        auto volumeDown = std::make_shared<exng::gui::Button>(
            sf::Vector2f(60, 50),
            sf::Vector2f(res.x / 2 - 220, res.y / 2 + 10),
            "-",
            [this]() {
                m_musicVolume = std::clamp(m_musicVolume - 10.f, 0.f, 100.f);
                exng::MusicManager::setVolume(m_musicVolume);
                refreshVolumeLabel();
            });

        auto volumeUp = std::make_shared<exng::gui::Button>(
            sf::Vector2f(60, 50),
            sf::Vector2f(res.x / 2 + 220, res.y / 2 + 10),
            "+",
            [this]() {
                m_musicVolume = std::clamp(m_musicVolume + 10.f, 0.f, 100.f);
                exng::MusicManager::setVolume(m_musicVolume);
                refreshVolumeLabel();
            });

        auto fullscreenButton = std::make_shared<exng::gui::Button>(
            sf::Vector2f(300, 50),
            sf::Vector2f(res.x / 2, res.y / 2 + 100),
            "Fullscreen (F11)",
            []() { exng::context::requestFullscreenToggle(); });

        auto backButton = std::make_shared<exng::gui::Button>(
            sf::Vector2f(200, 50),
            sf::Vector2f(res.x / 2, res.y / 2 + 180),
            "Back",
            [this]() { m_settingsOpen = false; });

        m_settingsContainer.addComponent(title);
        m_settingsContainer.addComponent(volumeLabel);
        m_settingsContainer.addComponent(volumeBar);
        m_settingsContainer.addComponent(volumeDown);
        m_settingsContainer.addComponent(volumeUp);
        m_settingsContainer.addComponent(fullscreenButton);
        m_settingsContainer.addComponent(backButton);

        refreshVolumeLabel();
    }

    void MainMenu::refreshVolumeLabel()
    {
        auto label = m_settingsContainer.getComponent<exng::gui::Label>(VolumeLabel);
        auto bar = m_settingsContainer.getComponent<exng::gui::ProgressBar>(VolumeBar);

        if (label) {
            label->setString("Music  " + std::to_string(static_cast<int>(m_musicVolume)) + "%");
            label->centerOrigin();
        }
        if (bar)
            bar->setProgress(m_musicVolume / 100.f);
    }

    void MainMenu::refreshStatusLabel()
    {
        auto label = m_guiContainer.getComponent<exng::gui::Label>(StatusLabel);
        if (!label)
            return;

        std::string text;
        sf::Color color = sf::Color::White;

        switch (m_displayedStatus) {
            case Status::Idle:
                text = "";
                break;
            case Status::Connecting:
                text = "Connecting...";
                break;
            case Status::Refused:
                text = "Connection refused by the server";
                color = sf::Color(230, 90, 90);
                break;
            case Status::TimedOut:
                text = "No answer from the server";
                color = sf::Color(230, 90, 90);
                break;
            case Status::BadAddress:
                text = "Invalid IP address";
                color = sf::Color(230, 90, 90);
                break;
            case Status::BadPort:
                text = "Invalid port (1-65535)";
                color = sf::Color(230, 90, 90);
                break;
        }

        label->setString(text);
        label->getText().setFillColor(color);
        label->centerOrigin();
    }

    void MainMenu::onPlayClicked()
    {
        if (m_waitingForConnection)
            return;

        auto ipInput = m_guiContainer.getComponent<exng::gui::InputBox>(IpInput);
        auto portInput = m_guiContainer.getComponent<exng::gui::InputBox>(PortInput);

        std::string ip = ipInput->getInputString();
        std::string port = portInput->getInputString();

        if (ip.empty() || sf::IpAddress(ip) == sf::IpAddress::None) {
            m_status = Status::BadAddress;
            return;
        }

        // stoi throws on anything that is not a number: the menu must not take
        // the whole client down because of a typo
        int portNumber = 0;
        try {
            std::size_t consumed = 0;
            portNumber = std::stoi(port, &consumed);
            if (consumed != port.size())
                throw std::invalid_argument("trailing characters");
        } catch (const std::exception &) {
            m_status = Status::BadPort;
            return;
        }

        if (portNumber <= 0 || portNumber > 65535) {
            m_status = Status::BadPort;
            return;
        }

        m_UDPclient.connect(ip, static_cast<unsigned short>(portNumber), MessageType::ConnectionRequest);
        m_status = Status::Connecting;
        m_waitingForConnection = true;
        m_connectionTimer = 0.f;
    }

    void MainMenu::processEvents(sf::Event &event)
    {
        processNetKeyEvents(event);

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
            if (m_settingsOpen) {
                m_settingsOpen = false;
                return;
            }
        }

        if (m_settingsOpen)
            m_settingsContainer.handleEvent(event);
        else
            m_guiContainer.handleEvent(event);
    }

    void MainMenu::update(float dt)
    {
        if (m_UDPclient.isConnected())
        {
            exng::logger::success() << "Connected to server";

            m_waitingForConnection = false;

            if (!m_sceneManager.isSceneLoaded("Game"))
                m_sceneManager.loadScene("Game", std::make_shared<scene::Game>(m_UDPclient, m_sceneManager, m_playerServerId));
            m_sceneManager.switchScene("Game");
            return;
        }

        if (m_waitingForConnection)
        {
            m_connectionTimer += dt;
            if (m_connectionTimer >= m_connectionTimeout)
            {
                m_waitingForConnection = false;
                m_connectionTimer = 0.f;
                m_status = Status::TimedOut;
                exng::logger::error() << "Connection timed out";
            }
        }

        // the status can be set from the network thread: only touch the GUI
        // from here
        Status status = m_status;
        if (status != m_displayedStatus) {
            if (status == Status::Refused) {
                m_waitingForConnection = false;
                m_connectionTimer = 0.f;
            }
            m_displayedStatus = status;
            refreshStatusLabel();
        }

        if (m_settingsOpen)
            m_settingsContainer.update();
        else
            m_guiContainer.update();

        m_background.update(dt);
    }

    void MainMenu::render(exng::Window &target)
    {
        m_background.render(target);
        if (m_settingsOpen)
            m_settingsContainer.render(target);
        else
            m_guiContainer.render(target);
    }
}
