/*
** EPITECH PROJECT, 2024
** B-CPP-500-STG-5-2-rtype-julian.lambert
** File description:
** DisconnectionSystem
*/

#ifndef RTYPE_SERVER_DISCONNECTION_SYSTEM_HPP
#define RTYPE_SERVER_DISCONNECTION_SYSTEM_HPP

// engine includes
#include "core/ecs/system/system.hpp"
#include "core/ecs/coordinator.hpp"
#include "core/transform/Transform.hpp"
#include "core/net/UDPServer.hpp"
#include "helper/SafeDequeue.hpp"

// server includes
#include "shared/components/components.hpp"
#include "shared/include/protocol.h"

using ClientInfo = exng::net::UDPServer::Client;

namespace rtype::sys
{

    class Disconnection : public exng::sys::System
    {
        public:
            Disconnection(exng::Coordinator &coordinator) : System(coordinator) {}

            void update(exng::net::UDPServer& server, exng::SafeDequeue<ClientInfo>& disconnectionQueue, exng::SafeDequeue<exng::Entity>& entitiesToDestroy)
            {
                while (!disconnectionQueue.empty()) {
                    auto client = disconnectionQueue.front();

                    for (auto entity : mEntities) {
                        auto& networdID = mCoordinator.getComponent<comp::NetworkIdentity>(entity);

                        if (networdID.address != client.address || networdID.port != client.port)
                            continue;

                        exng::logger::log() << "Client " << networdID.address << ":" << networdID.port << " disconnected. ID: " << entity;
                        entitiesToDestroy.push(entity);
                        server.removeClient({networdID.address, networdID.port});
                        exng::net::Packet response;
                        response << MessageType::Disconnection << entity;
                        server.reliableNotifyPacket(response);
                        disconnectionQueue.pop();
                    }
                }
            }
    };
}

#endif //RTYPE_SERVER_DISCONNECTION_SYSTEM_HPP