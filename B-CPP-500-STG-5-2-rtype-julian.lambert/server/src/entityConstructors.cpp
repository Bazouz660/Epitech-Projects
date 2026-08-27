/*
** EPITECH PROJECT, 2024
** B-CPP-500-STG-5-2-rtype-julian.lambert
** File description:
** entityConstructors
*/

#include "server/include/entityConstructors.h"
#include "server/include/teams.h"
#include "helper/info/context.hpp"
#include "shared/components/components.hpp"
#include <cmath>

namespace rtype::constructors {
    exng::Entity createPlayer(exng::Coordinator& coordinator, std::string address, unsigned short port, uint8_t playerNum)
    {
        exng::Entity player = coordinator.createEntity();

        comp::Transform playerTransform;
        playerTransform.setPosition(0, 1080 / 2);
        playerTransform.setRotation(0);
        playerTransform.setScale(3, 3);

        comp::Rigidbody playerRigidbody;
        playerRigidbody.velocity = {0, 0};
        playerRigidbody.acceleration = {0, 0};
        playerRigidbody.friction = 0.9f;

        comp::AABB playerAABB;
        playerAABB.localBounds = {0, 0, 32, 16};
        playerAABB.globalBounds = {0, 0, 32, 16};

        comp::NetworkIdentity playerNetworkIdentity;
        playerNetworkIdentity.address = address;
        playerNetworkIdentity.port = port;

        comp::NetSync playerNetSync;
        playerNetSync.type = EntityType::Player;

        comp::InputStates playerInputQueue; // Add inputQueue component

        comp::PlayerNumber playerNumber;
        playerNumber.number = playerNum;

        comp::Health playerHealth;
        playerHealth.maxHp = 3;
        playerHealth.hp = 3;
        playerHealth.cooldown = 0.2f;
        playerHealth.cooldownTimeLeft = 0.f;

        comp::Team playerTeam;
        playerTeam.val = teams::Players;

        comp::Damage playerDamage;
        playerDamage.val = 1;

        comp::Speed playerSpeed;
        playerSpeed.val = 300;

        comp::ShootingSpeed playerShootingSpeed;
        playerShootingSpeed.cooldown = 0.3f;
        playerShootingSpeed.timeLeft = 0;

        comp::Name playerName;
        playerName.val = "Player " + std::to_string(playerNum);

        coordinator.addComponent(player, playerTransform);
        coordinator.addComponent(player, playerRigidbody);
        coordinator.addComponent(player, playerAABB);
        coordinator.addComponent(player, playerNetworkIdentity);
        coordinator.addComponent(player, playerInputQueue); // Add inputQueue component
        coordinator.addComponent(player, playerNumber);
        coordinator.addComponent(player, playerNetSync);
        coordinator.addComponent(player, playerHealth);
        coordinator.addComponent(player, playerTeam);
        coordinator.addComponent(player, playerDamage);
        coordinator.addComponent(player, playerSpeed);
        coordinator.addComponent(player, playerShootingSpeed);
        coordinator.addComponent(player, comp::PlayerTag());
        coordinator.addComponent(player, playerName);

        return player;
    }

    exng::Entity createLaser(exng::Coordinator &coordinator, float posX, float posY, int team)
    {
        exng::Entity laser = coordinator.createEntity();

        comp::Transform laserTransform;
        laserTransform.setPosition(posX + 32, posY + 16);
        laserTransform.setRotation(0);
        laserTransform.setScale(1, 1);

        comp::Rigidbody laserRigidbody;
        laserRigidbody.velocity = {700, 0};
        laserRigidbody.acceleration = {0, 0};

        comp::AABB laserAABB;
        laserAABB.localBounds = {0, 0, 10, 2};
        laserAABB.globalBounds = {0, 0, 10, 2};

        comp::NetSync netSync;
        netSync.type = EntityType::Laser;

        comp::Lifetime lifetime;
        lifetime.maxtime = 5.f;

        comp::Health laserHealth;
        laserHealth.maxHp = 1;
        laserHealth.hp = 1;

        comp::Damage laserDamage;
        laserDamage.val = 1;

        comp::Team laserTeam;
        laserTeam.val = team;

        coordinator.addComponent(laser, laserTeam);
        coordinator.addComponent(laser, laserHealth);
        coordinator.addComponent(laser, laserDamage);
        coordinator.addComponent(laser, laserTransform);
        coordinator.addComponent(laser, laserRigidbody);
        coordinator.addComponent(laser, laserAABB);
        coordinator.addComponent(laser, netSync);
        coordinator.addComponent(laser, lifetime);

        return laser;
    }

    exng::Entity createBatEnemy(exng::Coordinator &coordinator, float posX, float posY, float speed)
    {
        exng::Entity enemy = coordinator.createEntity();

        comp::Transform enemyTransform;
        //random y position
        enemyTransform.setPosition(posX, posY);
        enemyTransform.setRotation(0);
        enemyTransform.setScale(3, 3);

        comp::Rigidbody enemyRigidbody;
        enemyRigidbody.velocity = {-speed, 0};
        enemyRigidbody.acceleration = {0, 0};

        comp::AABB enemyAABB;
        enemyAABB.localBounds = {0, 0, 24, 24};
        enemyAABB.globalBounds = {0, 0, 24, 24};

        comp::NetSync netSync;
        netSync.type = EntityType::BatEnemy;

        comp::Health enemyHealth;
        enemyHealth.maxHp = 1;
        enemyHealth.hp = 1;

        comp::Damage enemyDamage;
        enemyDamage.val = 1;

        comp::Speed enemySpeed;
        enemySpeed.val = speed;

        comp::Team enemyTeam;
        enemyTeam.val = teams::Enemies;

        coordinator.addComponent(enemy, enemyTransform);
        coordinator.addComponent(enemy, enemyRigidbody);
        coordinator.addComponent(enemy, enemyAABB);
        coordinator.addComponent(enemy, netSync);
        coordinator.addComponent(enemy, enemyHealth);
        coordinator.addComponent(enemy, enemyDamage);
        coordinator.addComponent(enemy, enemySpeed);
        coordinator.addComponent(enemy, enemyTeam);

        return enemy;
    }

    exng::Entity createObstacleBottom(exng::Coordinator &coordinator, float posX, float posY)
    {
        exng::Entity obstacle_b = coordinator.createEntity();

        comp::Transform obstacleTransform;

        obstacleTransform.setPosition(posX, posY);
        obstacleTransform.setRotation(0);
        obstacleTransform.setScale(2.f, 2.f);

        comp::Rigidbody obstacleRigidbody;
        obstacleRigidbody.velocity = {-325, 0};
        obstacleRigidbody.acceleration = {0, 0};

        comp::AABB obstacleAABB;
        obstacleAABB.localBounds = {0, 0, 66, 66};
        obstacleAABB.globalBounds = {0, 0, 66, 66};

        comp::NetSync netSync;
        netSync.type = EntityType::Obstacle_bottom;

        comp::Health obstacleHealth;
        obstacleHealth.maxHp = 9999;
        obstacleHealth.hp = 9999;

        comp::Damage obstacleDamage;
        obstacleDamage.val = 9999;

        comp::Speed obstacleSpeed;
        obstacleSpeed.val = 150;

        comp::Team obstacleTeam;
        obstacleTeam.val = teams::Obstacles;

        coordinator.addComponent(obstacle_b, obstacleTransform);
        coordinator.addComponent(obstacle_b, obstacleRigidbody);
        coordinator.addComponent(obstacle_b, obstacleAABB);
        coordinator.addComponent(obstacle_b, netSync);
        coordinator.addComponent(obstacle_b, obstacleHealth);
        coordinator.addComponent(obstacle_b, obstacleDamage);
        coordinator.addComponent(obstacle_b, obstacleSpeed);
        coordinator.addComponent(obstacle_b, obstacleTeam);

        return obstacle_b;
    }

    exng::Entity createObstacleTop(exng::Coordinator &coordinator, float posX, float posY)
    {
        exng::Entity obstacle_t = coordinator.createEntity();

        comp::Transform obstacleTransform;

        obstacleTransform.setPosition(posX, posY);
        obstacleTransform.setRotation(0);
        obstacleTransform.setScale(2.f, 2.f);

        comp::Rigidbody obstacleRigidbody;
        obstacleRigidbody.velocity = {-325, 0};
        obstacleRigidbody.acceleration = {0, 0};

        comp::AABB obstacleAABB;
        obstacleAABB.localBounds = {0, 0, 66, 66};
        obstacleAABB.globalBounds = {0, 0, 66, 66};

        comp::NetSync netSync;
        netSync.type = EntityType::Obstacle_top;

        comp::Health obstacleHealth;
        obstacleHealth.maxHp = 9999;
        obstacleHealth.hp = 9999;

        comp::Damage obstacleDamage;
        obstacleDamage.val = 9999;

        comp::Speed obstacleSpeed;
        obstacleSpeed.val = 150;

        comp::Team obstacleTeam;
        obstacleTeam.val = teams::Obstacles;

        coordinator.addComponent(obstacle_t, obstacleTransform);
        coordinator.addComponent(obstacle_t, obstacleRigidbody);
        coordinator.addComponent(obstacle_t, obstacleAABB);
        coordinator.addComponent(obstacle_t, netSync);
        coordinator.addComponent(obstacle_t, obstacleHealth);
        coordinator.addComponent(obstacle_t, obstacleDamage);
        coordinator.addComponent(obstacle_t, obstacleSpeed);
        coordinator.addComponent(obstacle_t, obstacleTeam);

        return obstacle_t;
    }

    exng::Entity createSnake(exng::Coordinator &coordinator, float posX, float posY, int nbChilds)
    {
        exng::Entity snake = coordinator.createEntity();

        comp::Transform snakeTransform;
        snakeTransform.setPosition(posX, posY);
        snakeTransform.setRotation(0);
        snakeTransform.setScale(3, 3);

        // create child snake
        if (nbChilds > 0) {
            exng::Entity childSnake = createSnake(coordinator, posX + 24, posY, nbChilds - 1);
            snakeTransform.addChild(childSnake, {0, 24}, true, true, true);
        }

        comp::Rigidbody snakeRigidbody;
        snakeRigidbody.velocity = {-200, 0};
        snakeRigidbody.acceleration = {0, 0};

        comp::AABB snakeAABB;
        snakeAABB.localBounds = {0, 0, 24, 24};
        snakeAABB.globalBounds = {0, 0, 24, 24};

        comp::NetSync netSync;
        netSync.type = EntityType::Snake;

        comp::Health snakeHealth;
        snakeHealth.maxHp = 1;
        snakeHealth.hp = 1;

        comp::Damage snakeDamage;
        snakeDamage.val = 1;

        comp::Speed snakeSpeed;
        snakeSpeed.val = 200;

        comp::Team snakeTeam;
        snakeTeam.val = teams::Enemies;

        coordinator.addComponent(snake, snakeTransform);
        coordinator.addComponent(snake, snakeRigidbody);
        coordinator.addComponent(snake, snakeAABB);
        coordinator.addComponent(snake, netSync);
        coordinator.addComponent(snake, snakeHealth);
        coordinator.addComponent(snake, snakeDamage);
        coordinator.addComponent(snake, snakeSpeed);
        coordinator.addComponent(snake, snakeTeam);

        return snake;
    }

}