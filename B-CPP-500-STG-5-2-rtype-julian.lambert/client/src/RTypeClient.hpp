/*
** EPITECH PROJECT, 2023
** B-CPP-500-STG-5-2-rtype-julian.lambert
** File description:
** RTypeClient
*/

#ifndef RTYPE_CLIENT_HPP
#define RTYPE_CLIENT_HPP

// project includes
#include "common.h"
#include "shared/include/protocol.h"
#include "shared/components/components.hpp"

// std includes
#include <thread>
#include <atomic>
#include <unordered_map>
#include <condition_variable>
#include <mutex>

// client includes
#include "systems/systems.hpp"

// engine includes
#include "logger.hpp"
#include "core/chrono/Chrono.hpp"
#include "core/window/Window.hpp"
#include "core/net/UDPClient.hpp"
#include "core/exception/Exception.hpp"
#include "core/event/Keyboard.hpp"
#include "core/ecs/coordinator.hpp"
#include "core/scene/SceneManager.hpp"

namespace rtype {

class RTypeClient {

public:
    RTypeClient();
    ~RTypeClient();

    void run();

    private:
        std::atomic<bool> m_shouldClose = false;
        std::thread m_netClientThread;
        exng::net::UDPClient m_UDPclient;

        float m_tickRate = 1.f / 30.0f;
        float m_tickTimer = 0.f;

        float m_disconnectionTimeout = 1.f;
        float m_disconnectionTimer = 0.f;
        std::condition_variable m_disconnectionCV;
        std::mutex m_disconnectionMutex;

        ////////////////////////////////////////////////

        ////////////////////////////////////////////////

        exng::Window m_window;
        sf::Event m_event;
        exng::Chrono m_logicChrono;
        exng::SceneManager m_sceneManager;

        void runGame();
        void runNetwork();
};

}

#endif //RTYPE_CLIENT_HPP