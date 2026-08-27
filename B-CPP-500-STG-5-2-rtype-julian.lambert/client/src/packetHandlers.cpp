/*
** EPITECH PROJECT, 2023
** B-CPP-500-STG-5-2-rtype-julian.lambert
** File description:
** packetHandlers
*/

// client includes
#include "scenes/Game.hpp"
#include "scenes/MainMenu.hpp"

// server includes
#include "shared/include/entityType.h"


namespace rtype {

    void scene::MainMenu::handleConnectionRefused(exng::net::Packet &packet, exng::net::UDPClient &client) {
        exng::logger::error() << "Connection refused";
        m_UDPclient.setConnected(false);
        // read back by update(), which owns the GUI
        m_status = Status::Refused;
    }

    void scene::MainMenu::handleConnectionAccepted(exng::net::Packet &packet, exng::net::UDPClient &client) {
        exng::Entity serverID;
        packet >> serverID;

        exng::logger::log() << "Connection accepted by server. Entity ID: " << serverID;

        m_UDPclient.setConnected(true);

        m_playerServerId = serverID;
    }

    void scene::Game::handleNewEntity(exng::net::Packet &packet, exng::net::UDPClient &client)
    {
        exng::Entity serverID;
        EntityType type;
        packet >> serverID >> type;

        try {
            auto entity = m_entityFactory.createEntity(type, m_coordinator, packet);
            m_clientToServerEntities[serverID] = entity;
            if (serverID == m_playerServerId) {
                m_playerClientId = std::make_unique<exng::Entity>(entity);
            }
        } catch (std::exception &e) {
            exng::logger::error() << "Failed to create entity: " << e.what();
        }
    }

    void scene::Game::handlePing(exng::net::Packet &packet, exng::net::UDPClient &client)
    {
        exng::logger::log() << "Received ping back from server";
    }

    void scene::Game::handleServerStopped(exng::net::Packet &packet, exng::net::UDPClient &client) {
        exng::logger::error() << "Lost connection to server, the server stopped";
        m_UDPclient.setConnected(false);
        // handled by update(), on the game thread
        m_serverStopped = true;
    }

    void scene::Game::handleEntityPositionUpdate(exng::net::Packet &packet, exng::net::UDPClient &client) {
        exng::Entity serverID;
        float posX, posY, rot, velX, velY;
        packet >> serverID >> posX >> posY >> velX >> velY >> rot;

        exng::Entity entityId;
        try {
            entityId = m_clientToServerEntities.at(serverID);
        } catch (std::out_of_range &e) {
            //exng::logger::warn() << "Received position update for unknown entity " << serverID;
            return;
        }

        if (!m_coordinator.hasComponent<comp::Transform>(entityId)) {
            exng::logger::error() << "Entity " << entityId << " has no transform component";
            return;
        }

        if (m_coordinator.hasComponent<comp::Rigidbody>(entityId)) {
            auto &rigidbody = m_coordinator.getComponent<comp::Rigidbody>(entityId);

            exng::Vector2f oldVel = rigidbody.velocity;

            rigidbody.velocity.x = velX;
            rigidbody.velocity.y = velY;

            // compute the average velocity
            rigidbody.velocity.x = (rigidbody.velocity.x + oldVel.x) / 2.f;
            rigidbody.velocity.y = (rigidbody.velocity.y + oldVel.y) / 2.f;

            if (rigidbody.velocity.x < 0.1f && rigidbody.velocity.x > -0.1f) {
                rigidbody.velocity.x = 0.f;
            }
            if (rigidbody.velocity.y < 0.1f && rigidbody.velocity.y > -0.1f) {
                rigidbody.velocity.y = 0.f;
            }
        }

        auto &transform = m_coordinator.getComponent<comp::Transform>(entityId);
        transform.setPosition({posX, posY});
        transform.setRotation(rot);
    }

    void scene::Game::handleDisconnection(exng::net::Packet &packet, exng::net::UDPClient &client) {
        exng::Entity serverID;
        packet >> serverID;

        exng::logger::log() << "Player " << serverID << " disconnected";

        exng::Entity entityId;
        try {
            entityId = m_clientToServerEntities.at(serverID);
        } catch (std::out_of_range &e) {
            exng::logger::warn() << "Received disconnection for unknown entity " << serverID;
            return;
        }

        auto &entities = m_coordinator.getEntities();
        auto entity = std::find_if(entities.begin(), entities.end(), [entityId](auto &entity) {
            return entity == entityId;
        });

        if (entity == entities.end()) {
            exng::logger::warn() << "Received disconnection for unknown entity " << entityId;
            return;
        }

        // if the disconnected entity is the player, disconnect from the server
        if (m_playerClientId && entityId == *m_playerClientId) {
            m_UDPclient.setConnected(false);
        }
    }

    void scene::Game::handleEntityDestroyed(exng::net::Packet &packet, exng::net::UDPClient &client) {
        exng::Entity serverID;
        packet >> serverID;

        //exng::logger::log() << "Entity " << serverID << " destroyed";

        exng::Entity entityId;
        try {
            entityId = m_clientToServerEntities.at(serverID);
        } catch (std::out_of_range &e) {
            exng::logger::warn() << "Received destruction for unknown entity " << serverID;
            return;
        }

        m_entitiesToDestroy.push(std::make_pair(serverID, false));
    }

    void scene::Game::handleHitboxUpdate(exng::net::Packet &packet, exng::net::UDPClient &client) {
        exng::Entity serverID;
        float width, height;
        packet >> serverID >> width >> height;

        exng::Entity entityId;
        try {
            entityId = m_clientToServerEntities.at(serverID);
        } catch (std::out_of_range &e) {
            //exng::logger::warn() << "Received hitbox update for unknown entity " << serverID;
            return;
        }

        if (!m_coordinator.hasComponent<comp::Transform>(entityId))
            return;

        for (auto &child : m_coordinator.getComponent<comp::Transform>(entityId).getChildren()) {
            if (!m_coordinator.hasComponent<comp::AABB>(child.entity)) {
                continue;
            }

            auto &hitbox = m_coordinator.getComponent<comp::AABB>(child.entity);
            hitbox.localBounds.width = width;
            hitbox.localBounds.height = height;

            if (m_coordinator.hasComponent<comp::Drawable>(child.entity)) {
                auto &drawable = m_coordinator.getComponent<comp::Drawable>(child.entity);
                drawable.rectangle.shape.setSize({width, height});
            }
        }
    }

    void scene::Game::handlePlayerInfo(exng::net::Packet &packet, exng::net::UDPClient &client) {
        exng::Entity serverID;
        int hp, maxHp;
        std::string name;
        packet >> serverID >> hp >> maxHp;

        exng::Entity entityId;
        try {
            entityId = m_clientToServerEntities.at(serverID);
        } catch (std::out_of_range &e) {
            exng::logger::warn() << "Received player info for unknown entity " << serverID;
            return;
        }

        if (serverID == m_playerServerId) {
            m_playerHp = hp;
            m_playerMaxHp = maxHp;
        }

        if (!m_coordinator.hasComponent<comp::Transform>(entityId)) {
            return;
        }
    }
}