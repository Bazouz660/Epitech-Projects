/*
** EPITECH PROJECT, 2023
** B-YEP-400-STG-4-1-zappy-basile.trebus-hamann
** File description:
** context
*/

#include "context.hpp"

namespace zpy::context {

    static Camera *cameraInstance = nullptr;
    static Renderer *rendererInstance = nullptr;
    static std::map<std::string, Color> teamColors;

    void setCamera(const Camera &camera)
    {
        context::cameraInstance = const_cast<Camera *>(&camera);
    }

    Camera &getCamera()
    {
        return *context::cameraInstance;
    }

    void setRenderer(const Renderer &renderer)
    {
        context::rendererInstance = const_cast<Renderer *>(&renderer);
    }

    Renderer &getRenderer()
    {
        return *context::rendererInstance;
    }

    Color getTeamColor(const std::string &teamName)
    {
        if (teamColors.find(teamName) == teamColors.end())
            return {255, 255, 255, 255};
        return teamColors[teamName];
    }

    void addTeamColor(const std::string &teamName, const Color &color)
    {
        teamColors[teamName] = color;
    }

}