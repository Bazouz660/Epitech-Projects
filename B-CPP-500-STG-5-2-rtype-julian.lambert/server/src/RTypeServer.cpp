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

namespace rtype {

    std::atomic<bool> shouldClose = false;
    std::atomic<bool> stoppedFromSignal = false;

    static void sigintHandler(int signal)
    {
        if (signal == SIGINT) {
            shouldClose = true;
            stoppedFromSignal = true;
            std::cin.setstate(std::ios_base::eofbit);
        }
    }

    void RTypeServer::loadConfig()
    {
        // define default values
        m_config.setDefaultSetting("port", 5000)
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
        if (stoppedFromSignal) {
            exng::logger::log() << "Press enter to exit";
        }
    }

    void RTypeServer::runLogic()
    {
        while (!shouldClose) {
            // update clocks
            m_logicChrono.update();
            float dt = m_logicChrono.getFrameDt().asSeconds();

            // send periodic network data
            m_networkTimer += dt;
            if (m_networkTimer > m_udpServer.getTickRate()) {

                if (m_ready) {
                    m_enemySpawnSystem->update(m_networkTimer, m_udpServer);
                    m_obstacleBottomSpawnSystem->update(m_networkTimer, m_udpServer);
                    m_obstacleTopSpawnSystem->update(m_networkTimer, m_udpServer);
                    m_transformSystem->update();
                    m_aabbSystem->update();
                    m_inputSystem->update(m_networkTimer, m_udpServer);
                    m_movementSystem->update(m_networkTimer);
                    m_playerBoundariesSystem->update();
                    m_lifetimeSystem->update(m_udpServer, m_networkTimer, m_entitiesToDestroy);
                    m_damageSystem->update(m_networkTimer, m_entitiesToDestroy);
                    m_entityDestroyer->update(m_udpServer, m_entitiesToDestroy, m_destroyMutex);
                }

                m_sendNetData->update(m_udpServer);
                m_sendPlayerInfo->update(m_udpServer);
                m_disconnectionSystem->update(m_udpServer, m_disconnectionQueue, m_entitiesToDestroy);

                m_networkTimer = 0;
            }

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
            // send sigint to stop the server
            raise(SIGINT);
            return;
        }

        // runs the game until the server is asked to stop
        runLogic();
    }
}