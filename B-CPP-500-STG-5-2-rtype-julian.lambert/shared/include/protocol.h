/*
** EPITECH PROJECT, 2023
** B-CPP-500-STG-5-2-rtype-julian.lambert
** File description:
** protocol
*/

#ifndef RTYPE_PROTOCOL_HPP
#define RTYPE_PROTOCOL_HPP

#include <cstdint>
#include "core/net/Packet.hpp"

namespace rtype {

    enum MessageType : uint8_t
    {
        // Message sent by the client
        Ping = 1,           // no arguments
        ConnectionRequest,  // no arguments
        DisconnectionRequest,  // no arguments
        Input,              // uint32_t playerID, uint8_t input

        // Message sent by the server
        ServerStopped,      // no arguments
        ConnectionRefused,  // no arguments
        ConnectionAccepted, // uint32_t playerID
        Disconnection,      // uint32_t playerID
        NewEntity,          // uint32_t entityID, uint8_t entityType
        EntityDestroyed,    // uint32_t entityID
        EntityPositionUpdate,       // uint32_t entityID, float x, float y
        EntityHitboxUpdate,         // uint32_t entityID, float x, float y, float width, float height
        PlayerInfo,         // uint32_t entityID, uint16_t health << uint16_t maxHealth
    };

    // >> and << operators for MessageType
    inline exng::net::Packet &operator>>(exng::net::Packet &packet, MessageType &messageType) {
        uint8_t type;
        packet >> type;
        messageType = static_cast<MessageType>(type);
        return packet;
    }

    inline exng::net::Packet &operator<<(exng::net::Packet &packet, MessageType messageType) {
        packet << static_cast<uint8_t>(messageType);
        return packet;
    }
}

#endif //RTYPE_PROTOCOL_HPP