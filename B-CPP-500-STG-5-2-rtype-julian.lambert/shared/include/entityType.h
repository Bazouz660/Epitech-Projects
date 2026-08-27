/*
** EPITECH PROJECT, 2023
** B-CPP-500-STG-5-2-rtype-julian.lambert
** File description:
** protocol
*/

#ifndef RTYPE_ENTITY_TYPE_HPP
#define RTYPE_ENTITY_TYPE_HPP

#include <cstdint>
#include "core/net/Packet.hpp"

namespace rtype {

    enum class EntityType : uint16_t
    {
        Player,
        Laser,
        BatEnemy,
        Obstacle_top,
        Obstacle_bottom,
        Snake
    };

    // >> and << operators for EntityType
    inline exng::net::Packet &operator>>(exng::net::Packet &packet, EntityType &entityType) {
        uint16_t type;
        packet >> type;
        entityType = static_cast<EntityType>(type);
        return packet;
    }

    inline exng::net::Packet &operator<<(exng::net::Packet &packet, EntityType entityType) {
        packet << static_cast<uint16_t>(entityType);
        return packet;
    }

}

#endif //RTYPE_ENTITY_TYPE_HPP