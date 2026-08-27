/*
** EPITECH PROJECT, 2024
** B-CPP-500-STG-5-2-rtype-julian.lambert
** File description:
** entityConstructors
*/

#include "EntityFactory.hpp"

namespace rtype {

    void EntityFactory::registerConstructor(const EntityType& type, constructor constructor)
    {
        m_constructors.insert_or_assign(type, constructor);
    }

    exng::Entity EntityFactory::createEntity(const EntityType& type, exng::Coordinator& coordinator, exng::net::Packet& packet)
    {
        return m_constructors[type](coordinator, packet);
    }

}