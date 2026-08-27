/*
** EPITECH PROJECT, 2024
** B-CPP-500-STG-5-2-rtype-julian.lambert
** File description:
** entityConstructors
*/

#ifndef RTYPE_CLIENT_ENTITYCONSTRUCTORS_HPP
#define RTYPE_CLIENT_ENTITYCONSTRUCTORS_HPP

#include "core/ecs/coordinator.hpp"
#include "core/ecs/entity/entity.hpp"
#include "shared/include/entityType.h"

#include <string>
#include <unordered_map>

namespace rtype {

    class EntityFactory {
        public:
            using constructor = exng::Entity (*)(exng::Coordinator&, exng::net::Packet&);

            void registerConstructor(const EntityType& type, constructor constructor);
            exng::Entity createEntity(const EntityType& type, exng::Coordinator& coordinator, exng::net::Packet& packet);

        private:
            std::unordered_map<EntityType, constructor> m_constructors;
    };
}

#endif //RTYPE_CLIENT_ENTITYCONSTRUCTORS_HPP