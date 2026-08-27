/*
** EPITECH PROJECT, 2023
** B-CPP-500-STG-5-2-rtype-julian.lambert
** File description:
** packetHandlers
*/

#include "RTypeServer.hpp"
#include "shared/include/protocol.h"
#include "shared/include/entityType.h"

#include "server/include/entityConstructors.h"
#include "server/include/teams.h"

#include "server/include/common.h"

namespace rtype {

    void RTypeServer::handleInput(exng::net::Packet &packet, exng::net::UDPServer &server, const ClientInfo &client)
    {
        exng::Entity entityID;
        packet >> entityID;

        int input;
        packet >> input;

        bool state; // true = pressed, false = released
        packet >> state;

        if (m_coordinator.entityExists(entityID) == false) {
            exng::logger::warn() << "Received input from non-existing entity " << entityID;
            return;
        }

        if (m_coordinator.hasComponent<comp::InputStates>(entityID)) {
            comp::InputStates &inputQueue = m_coordinator.getComponent<comp::InputStates>(entityID);

            inputQueue.m_keys.insert_or_assign(static_cast<exng::Keyboard::Key>(input), state);
        }
    }

    void RTypeServer::handlePing([[maybe_unused]]exng::net::Packet &packet, exng::net::UDPServer &server, const ClientInfo &client)
    {
        exng::logger::log() << "Received ping from client " << client.address << " on port " << client.port;
        exng::net::Packet pongPacket;
        pongPacket << MessageType::Ping;
        server.sendPacket(pongPacket, client);
    }

    void RTypeServer::handleConnectionRequest(exng::net::Packet &packet, exng::net::UDPServer &server, const ClientInfo &client)
    {
        exng::logger::log() << "Received connection request from " << client.address << ":" << client.port;

        if (server.isNewClient(client.address, client.port)) {
            // refuse before creating anything, otherwise the player entity
            // would linger forever for a client that never joined
            if (m_udpServer.getNbClients() >= MAX_PLAYERS) {
                exng::net::Packet refusal;
                refusal << MessageType::ConnectionRefused;
                server.reliableSendPacket(refusal, client);
                exng::logger::error() << "Client " << client.address << ":" << client.port
                                      << " connection refused (server full)";
                return;
            }

            // add a new player entity in the coordinator
            exng::Entity newPlayer = constructors::createPlayer(m_coordinator, client.address, client.port, m_playerNumber++);
            exng::net::Packet response;

            {
                // notify all clients of the new player
                server.addClient(client.address, client.port);

                m_ready = true;

                response << MessageType::NewEntity << newPlayer << EntityType::Player << m_coordinator.getComponent<comp::PlayerNumber>(newPlayer).number;
                server.reliableNotifyPacket(response);

                exng::net::Packet response2;
                response2 << MessageType::ConnectionAccepted << newPlayer;
                server.reliableSendPacket(response2, client);
                exng::logger::success() << "Client " << client.address << ":" << client.port << " successfully connected. ID: " << newPlayer;

                // Send information about already connected players to the new player
                for (exng::Entity entity : m_coordinator.getEntities()) {
                    if (m_coordinator.hasComponent<comp::NetSync>(entity) && entity != newPlayer) {
                        exng::net::Packet existingPlayerPacket;
                        if (!m_coordinator.hasComponent<comp::NetSync>(entity)) {
                            exng::logger::error() << "Entity " << entity << " is of unknown type, skipping";
                            continue;
                        }
                        auto &netSync = m_coordinator.getComponent<comp::NetSync>(entity);

                        existingPlayerPacket << MessageType::NewEntity << entity << netSync.type;

                        if (netSync.type == EntityType::Player)
                            existingPlayerPacket << m_coordinator.getComponent<comp::PlayerNumber>(entity).number;

                        server.reliableSendPacket(existingPlayerPacket, client);
                    }
                }
            }
        }
    }

    void RTypeServer::handleDisconnectionRequest(exng::net::Packet &packet, exng::net::UDPServer &server, const ClientInfo &client)
    {
        exng::logger::log() << "Received disconnection request from " << client.address << ":" << client.port;

        m_disconnectionQueue.push(client);
    }

}