/*
** EPITECH PROJECT, 2023
** B-YEP-400-STG-4-1-zappy-basile.trebus-hamann
** File description:
** context
*/

#pragma once

#include "common.hpp"
#include "Camera.hpp"

namespace zpy {

    class Renderer;

    namespace context {
        void setCamera(const Camera &camera);
        Camera &getCamera();

        void setRenderer(const Renderer& renderer);
        Renderer& getRenderer();

        Color getTeamColor(const std::string& teamName);
        void addTeamColor(const std::string& teamName, const Color& color);
    }

}