/*
** EPITECH PROJECT, 2023
** B-CPP-500-STG-5-2-rtype-julian.lambert
** File description:
** Server
*/

// exng includes
#include "helper/info/logger.hpp"

// std includes
#include <atomic>

// rtype includes
#include "shared/include/protocol.h"
#include "RTypeServer.hpp"
#include "shared/components/components.hpp"

// signal
#include <csignal>
#include <thread>
#include <chrono>
#include <algorithm>

#ifdef _WIN32
    #ifndef WIN32_LEAN_AND_MEAN
        #define WIN32_LEAN_AND_MEAN
    #endif
    #ifndef NOMINMAX
        // windows.h defines min/max as macros, which breaks std::min/std::max
        #define NOMINMAX
    #endif
    #include <windows.h>
#endif

namespace rtype {

    std::atomic<bool> shouldClose = false;
    std::atomic<bool> stoppedFromSignal = false;

    static void requestShutdown()
    {
        shouldClose = true;
        stoppedFromSignal = true;
    }

    static void sigintHandler(int signal)
    {
        if (signal == SIGINT)
            requestShutdown();
    }

#ifdef _WIN32
    // The CRT SIGINT emulation does not cover every way a console window can
    // go away (close button, logoff, ...): handle those too.
    static BOOL WINAPI consoleCtrlHandler(DWORD type)
    {
        switch (type) {
            case CTRL_C_EVENT:
            case CTRL_BREAK_EVENT:
            case CTRL_CLOSE_EVENT:
            case CTRL_LOGOFF_EVENT:
            case CTRL_SHUTDOWN_EVENT:
                requestShutdown();
                return TRUE;
            default:
                return FALSE;
        }
    }
#endif

    void RTypeServer::loadConfig()
    {
        // define default values
        m_config.setDefaultSetting("port", 4040)
                .setDefaultSetting("net_tickrate", 30)
                .setDefaultSetting("logic_tickrate", 60);

        m_config.load("config.ini");
    }

    void RTypeServer::registerCommands()
    {
        m_shell.addCommand("stop", [this](std::vector<std::string> args) {
            this->stop();
            this->m_shell.stop();
        });

        m_shell.addCommand("help", [this](std::vector<std::string> args) {
            std::stringstream ss;
            ss << "Available commands:\n";
            for (auto &command : this->m_shell.getCommands()) {
                ss << "- " << command.first << "\n";
            }
            exng::logger::log() << ss.str();
        });
    }

    void RTypeServer::registerComponents()
    {
        // register components (ça dit au coordinator quels composants existent)
        m_coordinator.registerComponent<comp::Transform>();
        m_coordinator.registerComponent<comp::Rigidbody>();
        m_coordinator.registerComponent<comp::AABB>();
        m_coordinator.registerComponent<comp::NetworkIdentity>();
        m_coordinator.registerComponent<comp::InputStates>();
        m_coordinator.registerComponent<comp::PlayerNumber>();
        m_coordinator.registerComponent<comp::NetSync>();
        m_coordinator.registerComponent<comp::Health>();
        m_coordinator.registerComponent<comp::Damage>();
        m_coordinator.registerComponent<comp::Speed>();
        m_coordinator.registerComponent<comp::Team>();
        m_coordinator.registerComponent<comp::Lifetime>();
        m_coordinator.registerComponent<comp::ShootingSpeed>();
        m_coordinator.registerComponent<comp::PlayerTag>();
        m_coordinator.registerComponent<comp::Name>();
    }

    void RTypeServer::registerSystems()
    {
        m_transformSystem = m_coordinator.createSystem<sys::UpdateTransform,
            comp::Transform
        >();

        m_movementSystem = m_coordinator.createSystem<sys::MovementSystem,
            comp::Transform,
            comp::Rigidbody
        >();

        m_aabbSystem = m_coordinator.createSystem<sys::UpdateAABB,
            comp::Transform,
            comp::AABB
        >();

        m_inputSystem = m_coordinator.createSystem<sys::InputSystem,
            comp::InputStates,
            comp::NetworkIdentity,
            comp::Rigidbody,
            comp::Transform,
            comp::ShootingSpeed
        >();

        m_sendNetData = m_coordinator.createSystem<sys::SendNetData,
            comp::NetSync,
            comp::Transform
        >();

        m_disconnectionSystem = m_coordinator.createSystem<sys::Disconnection,
            comp::NetworkIdentity
        >();

        m_damageSystem = m_coordinator.createSystem<sys::DamageSystem,
            comp::AABB
        >();

        m_lifetimeSystem = m_coordinator.createSystem<sys::LifetimeSystem,
            comp::Lifetime
        >();

        m_playerBoundariesSystem = m_coordinator.createSystem<sys::PlayerBoundariesSystem,
            comp::Transform,
            comp::AABB,
            comp::PlayerTag
        >();

        m_sendPlayerInfo = m_coordinator.createSystem<sys::SendPlayerInfo,
            comp::Health,
            comp::PlayerTag
        >();

        m_entityDestroyer = m_coordinator.createSystem<sys::EntityDestroyer>();

        m_enemySpawnSystem = m_coordinator.createSystem<sys::EnemySpawnSystem>();

        m_obstacleBottomSpawnSystem = m_coordinator.createSystem<sys::ObstacleBottomSpawnSystem>();

        m_obstacleTopSpawnSystem = m_coordinator.createSystem<sys::ObstacleTopSpawnSystem>();
    }

    void RTypeServer::registerPacketHandlers()
    {
        m_udpServer.registerPacketHanlder(MessageType::ConnectionRequest, [this](exng::net::Packet &packet, exng::net::UDPServer &server, const ClientInfo &client) {
            this->handleConnectionRequest(packet, server, client);
        });
        m_udpServer.registerPacketHanlder(MessageType::Ping, [this](exng::net::Packet &packet, exng::net::UDPServer &server, const ClientInfo &client) {
            this->handlePing(packet, server, client);
        });
        m_udpServer.registerPacketHanlder(MessageType::Input, [this](exng::net::Packet &packet, exng::net::UDPServer &server, const ClientInfo &client) {
            this->handleInput(packet, server, client);
        });
        m_udpServer.registerPacketHanlder(MessageType::DisconnectionRequest, [this](exng::net::Packet &packet, exng::net::UDPServer &server, const ClientInfo &client) {
            this->handleDisconnectionRequest(packet, server, client);
        });
    }

    RTypeServer::RTypeServer()
    {
        // signal handling
        signal(SIGINT, sigintHandler);
    #ifdef _WIN32
        SetConsoleCtrlHandler(consoleCtrlHandler, TRUE);
    #endif

        // shell commands initialization
        registerCommands();

        // ECS initialization
        m_coordinator.init();
        registerComponents();
        registerSystems();

        // packet handlers registration
        registerPacketHandlers();

        // load config file
        loadConfig();
    }

    RTypeServer::~RTypeServer()
    {
        m_udpServer.stop(MessageType::ServerStopped);
        exng::logger::debug() << "sent server stopped message";
        m_shell.stop();
        exng::logger::log() << "Server stopped";
    }

    void RTypeServer::runLogic()
    {
        // both rates come from the config file: the simulation is stepped at
        // logic_tickrate, the state is broadcast at net_tickrate
        const float logicTickRate = 1.f / static_cast<float>(std::max(1, m_config.getSetting<int>("logic_tickrate")));
        const float netTickRate = m_udpServer.getTickRate();

        float logicTimer = 0.f;

        while (!shouldClose) {
            // update clocks
            m_logicChrono.update();
            float dt = m_logicChrono.getFrameDt().asSeconds();

            logicTimer += dt;
            m_networkTimer += dt;

            if (logicTimer >= logicTickRate) {
                if (m_ready) {
                    m_enemySpawnSystem->update(logicTimer, m_udpServer);
                    m_obstacleBottomSpawnSystem->update(logicTimer, m_udpServer);
                    m_obstacleTopSpawnSystem->update(logicTimer, m_udpServer);
                    m_transformSystem->update();
                    m_aabbSystem->update();
                    m_inputSystem->update(logicTimer, m_udpServer);
                    m_movementSystem->update(logicTimer);
                    m_playerBoundariesSystem->update();
                    m_lifetimeSystem->update(m_udpServer, logicTimer, m_entitiesToDestroy);
                    m_damageSystem->update(logicTimer, m_entitiesToDestroy);
                    m_entityDestroyer->update(m_udpServer, m_entitiesToDestroy, m_destroyMutex);
                }

                logicTimer = 0.f;
            }

            // send periodic network data
            if (m_networkTimer >= netTickRate) {
                m_sendNetData->update(m_udpServer);
                m_sendPlayerInfo->update(m_udpServer);
                m_disconnectionSystem->update(m_udpServer, m_disconnectionQueue, m_entitiesToDestroy);

                m_networkTimer = 0.f;
            }

            // without this the loop would spin at 100% of a core between ticks
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    }

    void RTypeServer::stop()
    {
        shouldClose = true;
    }

    void RTypeServer::run()
    {
        m_shell.start();

        try {
            m_udpServer.setTickRate(m_config.getSetting<int>("net_tickrate"));
            m_udpServer.start(m_config.getSetting<unsigned int>("port"));
        } catch (const std::exception &e) {
            exng::logger::error() << e.what();
            requestShutdown();
            return;
        }

        // runs the game until the server is asked to stop
        runLogic();
    }
}