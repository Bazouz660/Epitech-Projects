/*
** EPITECH PROJECT, 2023
** B-CPP-500-STG-5-2-rtype-julian.lambert
** File description:
** Server
*/

#ifndef RTYPE_SERVER_HPP
#define RTYPE_SERVER_HPP

// engine includes
#include "core/net/UDPServer.hpp"
#include "core/ecs/coordinator.hpp"
#include "core/ecs/entity/entity.hpp"
#include "core/config/Config.hpp"
#include "core/chrono/Chrono.hpp"
#include "helper/SafeDequeue.hpp"

// std includes
#include <thread>
#include <queue>

// server includes
#include "Shell.hpp"
#include "systems/systems.hpp"

using ClientInfo = exng::net::UDPServer::Client;

namespace rtype {
    class RTypeServer {
        public:
            RTypeServer();

            // Destructor, joins the subthreads if needed
            ~RTypeServer();

            // starts the server
            void run();

            // asks the server to stop
            void stop();

        private:
            // Packet handlershandlePing
            void registerPacketHandlers();
            void handlePing(exng::net::Packet &packet, exng::net::UDPServer &server, const ClientInfo &client);
            void handleConnectionRequest(exng::net::Packet &packet, exng::net::UDPServer &server, const ClientInfo &client);
            void handleDisconnectionRequest(exng::net::Packet &packet, exng::net::UDPServer &server, const ClientInfo &client);
            void handleInput(exng::net::Packet &packet, exng::net::UDPServer &server, const ClientInfo &client);
            void handleEntityDestructionValidation(exng::net::Packet &packet, exng::net::UDPServer &server, const ClientInfo &client);

            // test
            void handleCreateLaser(exng::net::Packet &packet, exng::net::UDPServer &server, const ClientInfo &client);
            void handleCreateEnemy(exng::net::Packet &packet, exng::net::UDPServer &server, const ClientInfo &client);
            void handleCreateObstacleBottom(exng::net::Packet &packet, exng::net::UDPServer &server, const ClientInfo &client);
            void handleCreateObstacleTop(exng::net::Packet &packet, exng::net::UDPServer &server, const ClientInfo &client);
            // ECS
            void registerComponents();
            void registerSystems();

            // shell
            void registerCommands();

            // config
            void loadConfig();

        private:

            // Config

            exng::Config m_config;

            ////////////////////////////////////////////////////////////////////////////////////////////////////

            // Shell for commands handling
            Shell m_shell;

            std::thread m_shellThread;

            ////////////////////////////////////////////////////////////////////////////////////////////////////

            // Game logic
            void runLogic();

            exng::Chrono m_logicChrono;

            ////////////////////////////////////////////////////////////////////////////////////////////////////

            // systems
            std::shared_ptr<sys::UpdateTransform> m_transformSystem; // needed to update the transform of entities
            std::shared_ptr<sys::MovementSystem> m_movementSystem; // needed to update the movement of entities, it could be replaced by a another system that would handle the movement of entities
            std::shared_ptr<sys::UpdateAABB> m_aabbSystem; // needed to update the AABB of entities
            std::shared_ptr<sys::InputSystem> m_inputSystem;
            std::shared_ptr<sys::SendNetData> m_sendNetData;
            std::shared_ptr<sys::Disconnection> m_disconnectionSystem;
            std::shared_ptr<sys::DamageSystem> m_damageSystem;
            std::shared_ptr<sys::LifetimeSystem> m_lifetimeSystem;
            std::shared_ptr<sys::EntityDestroyer> m_entityDestroyer;
            std::shared_ptr<sys::EnemySpawnSystem> m_enemySpawnSystem;
            std::shared_ptr<sys::ObstacleBottomSpawnSystem> m_obstacleBottomSpawnSystem;
            std::shared_ptr<sys::ObstacleTopSpawnSystem> m_obstacleTopSpawnSystem;
            std::shared_ptr<sys::PlayerBoundariesSystem> m_playerBoundariesSystem;
            std::shared_ptr<sys::SendPlayerInfo> m_sendPlayerInfo;

            // coordinator (needed to register systems and components and to create entities)
            exng::Coordinator m_coordinator;

            ////////////////////////////////////////////////////////////////////////////////////////////////////

            // network
            exng::Chrono m_networkChrono;
            exng::net::UDPServer m_udpServer;
            uint8_t m_playerNumber = 0;
            float m_networkTimer = 0.0f;
            std::atomic<bool> m_ready = false;

            exng::SafeDequeue<ClientInfo> m_disconnectionQueue;
            std::mutex m_destroyMutex;
            exng::SafeDequeue<exng::Entity> m_entitiesToDestroy;
    };
}

#endif //RTYPE_SERVER_HPP