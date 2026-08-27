/*
** EPITECH PROJECT, 2023
** B-YEP-400-STG-4-1-zappy-basile.trebus-hamann
** File description:
** GUI
*/

#pragma once

#include "common.hpp"
#include "Renderer.hpp"
#include "Client.hpp"

namespace zpy {

class GUI {

    public:
        GUI() = default;

        void init(int port, const std::string& host);
        void run();

        ~GUI() = default;

    private:
        uptr<Client> m_client;
        sptr<Renderer> m_renderer;
};

}