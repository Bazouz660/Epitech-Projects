/*
** EPITECH PROJECT, 2023
** RPG3
 *  Modified by: Clément Thomas
 *  Modified time: 2023-07-10 03:24:20
*/

#pragma once

#include "common.hpp"
#include "core/window/Window.hpp"
#include "core/window/view/View.hpp"

#include <atomic>

namespace exng
{
    namespace context
    {
        // `inline` matters here: with a plain `static` every translation unit
        // would get its own copy, so a resolution set from main() would not be
        // visible from the scenes.
        inline Vector2u targetResolution = {1920, 1080};
        inline std::atomic<bool> quitRequested = false;
        inline std::atomic<bool> fullscreenToggleRequested = false;

        inline void setTargetResolution(const Vector2u& resolution)
        {
            targetResolution = resolution;
        }

        inline void setTargetResolution(unsigned int x, unsigned int y)
        {
            targetResolution = {x, y};
        }

        inline Vector2u getTargetResolution()
        {
            return targetResolution;
        }

        // The GUI has no handle on the window: these let a scene ask the main
        // loop to shut down or to switch display mode.
        inline void requestQuit()
        {
            quitRequested = true;
        }

        inline bool isQuitRequested()
        {
            return quitRequested;
        }

        inline void requestFullscreenToggle()
        {
            fullscreenToggleRequested = true;
        }

        inline bool consumeFullscreenToggle()
        {
            return fullscreenToggleRequested.exchange(false);
        }
    }
}
