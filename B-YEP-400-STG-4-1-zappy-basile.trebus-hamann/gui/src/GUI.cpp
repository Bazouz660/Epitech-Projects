/*
** EPITECH PROJECT, 2023
** B-YEP-400-STG-4-1-zappy-basile.trebus-hamann
** File description:
** GUI
*/

#include "GUI.hpp"
#include <csignal>

namespace zpy {

void GUI::init(int port, const std::string &host)
{
    m_renderer = std::make_shared<Renderer>(1920 / 2, 1080 / 2, "Raylib_test");
	m_client = std::make_unique<Client>(*m_renderer);

	try {
		m_client->init(port, host);
		m_client->connect();
		m_client->authentify();
	} catch (const std::exception &e) {
		std::cerr << e.what() << std::endl;
		exit(84);
	}

    m_renderer->init();
}

void GUI::run()
{
	while (!m_renderer->shouldClose() && !m_client->shouldClose()) {
		m_client->update();
		m_renderer->update();
		m_renderer->draw();
		m_renderer->handleEvents();
	}
}

}
