/*
 * Filename: /home/basile/Projects/Ecole/Current/B-CPP-500-STG-5-2-rtype-julian.lambert/engine/src/engine/window/Window.cpp
 * Path: /home/basile/Projects/Ecole/Current/B-CPP-500-STG-5-2-rtype-julian.lambert/engine/src/engine/window
 * Created Date: Monday, December 11th 2023, 7:30:42 pm
 * Author: Basile
 * 
 * Copyright (c) 2023 Your Company
 */

#include "Window.hpp"
#include "core/window/view/View.hpp"
#include "helper/info/logger.hpp"

namespace exng {

    Window::Window()
    {
    }

    Window::~Window()
    {
    }

    void Window::create(const std::string& title, const Vector2u& size, bool fullscreen)
    {
        m_title = title;
        m_renderSize = size;

        setFullscreen(fullscreen);
    }

    void Window::setFullscreen(bool fullscreen)
    {
        m_fullscreen = fullscreen;

        if (fullscreen) {
            m_window.create(sf::VideoMode::getDesktopMode(), m_title, sf::Style::Fullscreen);
        } else {
            // A 1920x1080 window does not fit on a 1920x1080 desktop once the
            // title bar and the taskbar are taken into account, so scale the
            // window down until it fits while keeping the aspect ratio.
            sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
            float maxWidth = desktop.width * 0.9f;
            float maxHeight = desktop.height * 0.9f;

            float scale = std::min(maxWidth / static_cast<float>(m_renderSize.x),
                                   maxHeight / static_cast<float>(m_renderSize.y));
            if (scale > 1.f)
                scale = 1.f;

            unsigned int width = static_cast<unsigned int>(m_renderSize.x * scale);
            unsigned int height = static_cast<unsigned int>(m_renderSize.y * scale);

            m_window.create(sf::VideoMode(width, height), m_title,
                            sf::Style::Titlebar | sf::Style::Close);
        }

        applyWindowSettings();
    }

    void Window::applyWindowSettings()
    {
        applyLetterboxView();

        if (!m_iconPath.empty())
            setIcon(m_iconPath);
        if (m_framerateLimit > 0)
            m_window.setFramerateLimit(m_framerateLimit);
        m_window.setVerticalSyncEnabled(m_verticalSync);
    }

    bool Window::isFullscreen() const
    {
        return m_fullscreen;
    }

    void Window::applyLetterboxView()
    {
        // Keep drawing in m_renderSize coordinates whatever the window size is,
        // and add black bars instead of stretching when ratios differ.
        sf::Vector2u windowSize = m_window.getSize();
        if (windowSize.x == 0 || windowSize.y == 0)
            return;

        float windowRatio = static_cast<float>(windowSize.x) / static_cast<float>(windowSize.y);
        float renderRatio = static_cast<float>(m_renderSize.x) / static_cast<float>(m_renderSize.y);

        float width = 1.f;
        float height = 1.f;

        if (windowRatio > renderRatio)
            width = renderRatio / windowRatio;
        else
            height = windowRatio / renderRatio;

        sf::View view(sf::FloatRect(0.f, 0.f,
                                    static_cast<float>(m_renderSize.x),
                                    static_cast<float>(m_renderSize.y)));
        view.setViewport(sf::FloatRect((1.f - width) / 2.f, (1.f - height) / 2.f, width, height));
        m_window.setView(view);
    }

    void Window::setIcon(const std::string& path)
    {
        sf::Image icon;
        if (!icon.loadFromFile(path)) {
            logger::warn() << "Could not load the window icon: " << path;
            return;
        }
        m_iconPath = path;
        m_window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    }

    Vector2u Window::getRenderSize() const
    {
        return m_renderSize;
    }

    Vector2f Window::mapPixelToCoords(int x, int y) const
    {
        sf::Vector2f coords = m_window.mapPixelToCoords(sf::Vector2i(x, y));
        return Vector2f(coords.x, coords.y);
    }

    void Window::close()
    {
        m_window.close();
    }

    void Window::clear()
    {
        m_window.clear();
    }

    void Window::draw(const sf::Drawable& drawable, const sf::RenderStates& states)
    {
        m_window.draw(drawable, states);
    }

    void Window::display()
    {
        m_window.display();
    }

    bool Window::isOpen() const
    {
        return m_window.isOpen();
    }

    Vector2u Window::getSize() const
    {
        auto size = m_window.getSize();
        return Vector2u(size.x, size.y);
    }

    Vector2f Window::getCenter() const
    {
        auto size = m_window.getSize();
        return Vector2f(size.x / 2, size.y / 2);
    }

    Vector2f Window::getPosition() const
    {
        auto pos = m_window.getPosition();
        return Vector2f(pos.x, pos.y);
    }

    bool Window::pollEvent(sf::Event& event)
    {
        return m_window.pollEvent(event);
    }

    sf::RenderWindow& Window::getHandle()
    {
        return m_window;
    }

    void Window::setFramerateLimit(unsigned int limit)
    {
        m_framerateLimit = limit;
        m_window.setFramerateLimit(limit);
    }

    void Window::setVerticalSyncEnabled(bool enabled)
    {
        m_verticalSync = enabled;
        m_window.setVerticalSyncEnabled(enabled);
    }

    void Window::setView(const View& view)
    {
        sf::View sfmlView;
        sfmlView.setCenter(view.getCenter().x, view.getCenter().y);
        sfmlView.setSize(view.getSize().x, view.getSize().y);
        sfmlView.setRotation(view.getRotation());
        sfmlView.setViewport(sf::FloatRect(view.getViewport().left, view.getViewport().top, view.getViewport().width, view.getViewport().height));
        m_window.setView(sfmlView);
    }

    View Window::getView() const
    {
        auto sfmlView = m_window.getView();
        View view;
        view.setCenter(sfmlView.getCenter().x, sfmlView.getCenter().y);
        view.setSize(sfmlView.getSize().x, sfmlView.getSize().y);
        view.setRotation(sfmlView.getRotation());
        view.setViewport(FloatRect(sfmlView.getViewport().left, sfmlView.getViewport().top, sfmlView.getViewport().width, sfmlView.getViewport().height));
        return view;
    }

} // namespace exng