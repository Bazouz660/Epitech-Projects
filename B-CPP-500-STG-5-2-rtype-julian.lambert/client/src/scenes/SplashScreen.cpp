/*
** EPITECH PROJECT, 2024
** B-CPP-500-STG-5-2-rtype-julian.lambert
** File description:
** SplashScreen
*/

#include "SplashScreen.hpp"
#include "client/src/scenes/MainMenu.hpp"
#include "core/resource_manager/ResourceManager.hpp"
#include "core/scene/SceneManager.hpp"
#include "helper/info/context.hpp"

namespace rtype::scene {
    SplashScreen::SplashScreen(exng::net::UDPClient &UDPclient, exng::SceneManager &sceneManager)
        : m_udpClient(UDPclient), AScene(sceneManager)
    {
        auto& texture = exng::ResourceManager::getTexture("icon", "youpiLogo");
        texture.setSmooth(true);
        m_logo.setTexture(texture);
        m_logo.setOrigin(m_logo.getGlobalBounds().width / 2, m_logo.getGlobalBounds().height / 2);
        m_logo.setScale(0.3, 0.3);
        m_logo.setPosition(exng::context::getTargetResolution().x / 2, exng::context::getTargetResolution().y / 2);

        auto& loadingTexture = exng::ResourceManager::getTexture("icon", "loading");
        loadingTexture.setSmooth(true);
        m_loadingCircle.setTexture(&loadingTexture);
        m_loadingCircle.setRadius(30);
        m_loadingCircle.setOrigin(m_loadingCircle.getGlobalBounds().width / 2, m_loadingCircle.getGlobalBounds().height / 2);
        m_loadingCircle.setPosition(exng::context::getTargetResolution().x * 0.95f, exng::context::getTargetResolution().y * 0.9f);

        m_loadingMinTime = 5.f;
    }

    SplashScreen::~SplashScreen()
    {
    }

    void SplashScreen::processEvents(sf::Event &event)
    {
    }

    void SplashScreen::update(float dt)
    {
        static bool loaded = false;

        if (!exng::ResourceManager::isLoading() && m_loadingTimer > m_loadingMinTime && loaded) {
            m_sceneManager.loadScene("MainMenu", std::make_shared<scene::MainMenu>(m_udpClient, m_sceneManager));
            m_sceneManager.switchScene("MainMenu");
        }

        m_loadingTimer += dt;
        m_fade.update(dt);
        m_logo.setColor(sf::Color(255, 255, 255, 255 * m_fade.getAlpha()));

        m_loadingCircle.rotate(360 * dt);

        m_delayedTimer += dt;
        if (m_delayedTimer > 0.0 && !loaded) {
            loaded = true;
            exng::ResourceManager::loadFromFolder(exng::ResourceType::Texture, "asset/texture", true);
            exng::ResourceManager::loadFromFolder(exng::ResourceType::Font, "asset/font", true);
            exng::ResourceManager::loadFromFolder(exng::ResourceType::SoundBuffer, "asset/audio/sound", true);
            exng::ResourceManager::loadFromFolder(exng::ResourceType::Music, "asset/audio/music", true);
        }
    }

    void SplashScreen::render(exng::Window &target)
    {
        target.draw(m_logo);
        target.draw(m_loadingCircle);
    }

    void SplashScreen::onEnter()
    {
        m_fade = exng::effect::Fade(2, 2);
    }

    void SplashScreen::onExit()
    {
    }
}