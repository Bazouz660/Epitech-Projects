/*
** EPITECH PROJECT, 2024
** B-CPP-500-STG-5-2-rtype-julian.lambert
** File description:
** entityConstructors
*/

#ifndef RTYPE_SERVER_ENTITYCONSTRUCTORS_HPP
#define RTYPE_SERVER_ENTITYCONSTRUCTORS_HPP

#include "core/ecs/coordinator.hpp"
#include "core/ecs/entity/entity.hpp"

#include <string>

namespace rtype::constructors {

    exng::Entity createPlayer(exng::Coordinator& coordinator, std::string address, unsigned short port, uint8_t playerNum);
    exng::Entity createLaser(exng::Coordinator &coordinator, float x, float y, int team);
    exng::Entity createBatEnemy(exng::Coordinator &coordinator, float posX, float posY, float speed);
    exng::Entity createObstacleBottom(exng::Coordinator &coordinator, float posX, float posY);
    exng::Entity createObstacleTop(exng::Coordinator &coordinator, float posX, float posY);
    exng::Entity createSnake(exng::Coordinator &coordinator, float posX, float posY, int nbchilds);
}

#endif //RTYPE_SERVER_ENTITYCONSTRUCTORS_HPP