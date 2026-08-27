/*
 * Filename: Window.hpp
 * Path: engine/src/engine/window
 * Created Date: Monday, December 11th 2023, 7:30:35 pm
 * Author: Basile
 *
 * Copyright (c) 2023 Your Company
 */

#ifndef EXNG_WINDOW_HPP_
#define EXNG_WINDOW_HPP_

#include "common.hpp"
#include "core/vector2/Vector2.hpp"

namespace exng {

    class View;

    // Encapsulate the sfml render window
    class Window
    {
    public:
        Window();
        ~Window();

        // Create the window.
        // `size` is the resolution the game draws at; the actual window is
        // shrunk to fit the desktop when needed, the drawing resolution being
        // preserved through a letterboxed view.
        void create(const std::string& title, const Vector2u& size, bool fullscreen = false);

        // Set the window icon from an image file (silently ignored if missing)
        void setIcon(const std::string& path);

        // Toggle between fullscreen and windowed mode, keeping title and size
        void setFullscreen(bool fullscreen);
        bool isFullscreen() const;

        bool pollEvent(sf::Event& event);

        // Resolution the game logic draws at, whatever the real window size is
        Vector2u getRenderSize() const;

        // Convert window pixel coordinates (as found in mouse events) into the
        // coordinates used by the game, accounting for scaling and letterboxing
        Vector2f mapPixelToCoords(int x, int y) const;

        // Destroy the window
        void close();

        // Clear the window
        void clear();

        // Draw a drawable object
        void draw(const sf::Drawable& drawable, const sf::RenderStates& states = sf::RenderStates::Default);

        void setFramerateLimit(unsigned int limit);
        void setVerticalSyncEnabled(bool enabled);

        void setView(const View& view);
        View getView() const;

        // Display the window
        void display();

        // Check if the window is open
        bool isOpen() const;

        // Get the window size
        Vector2u getSize() const;

        Vector2f getCenter() const;

        Vector2f getPosition() const;

        sf::RenderWindow& getHandle();

    private:
        void applyLetterboxView();

        // switching between windowed and fullscreen recreates the underlying
        // window, so everything set on it has to be remembered and reapplied
        void applyWindowSettings();

        sf::RenderWindow m_window;
        std::string m_title;
        std::string m_iconPath;
        Vector2u m_renderSize = {1920, 1080};
        bool m_fullscreen = false;
        unsigned int m_framerateLimit = 0;
        bool m_verticalSync = false;
    };
} // namespace exng

#endif // EXNG_WINDOW_HPP_