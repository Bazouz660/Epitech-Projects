/*
** EPITECH PROJECT, 2023
** B-YEP-400-STG-4-1-zappy-basile.trebus-hamann
** File description:
** Renderer
*/

#pragma once

#include "common.hpp"
#include "Grid.hpp"
#include "Camera.hpp"
#include "Chrono.hpp"
#include "Fog.hpp"
#include "Trantorian.hpp"
#include "Hud.hpp"

namespace zpy {

class Renderer {

    public:
        Renderer() = default;
        Renderer(unsigned int width, unsigned int height, const std::string &title);

        void init(unsigned int tickRate = 60);

        void update();
        void draw();
        void handleEvents();

        bool shouldClose() const;
        void close();

        Vec2 getWindowSize();

        Grid& getGrid() const;
        Camera& getCamera();

        void setTimeUnit(unsigned int timeUnit);

        void incrementTick();
        unsigned int getTickCount() const;
        void setTickCount(unsigned int tickCount);

        void addTeam(const std::string& teamName);
        void addPlayer(const Vec2& pos, Trantorian::Orientation orientation, unsigned int level, int id, std::string teamName);
        void updateHudInfo();
        void updateHudFocusedPlayer();

        std::vector<sptr<Trantorian>>& getPlayers();
        sptr<Trantorian> getPlayer(int id);

        void setFocusedPlayer(Trantorian* player);
        Trantorian* getFocusedPlayer() const { return m_focusedPlayer; }

        void setWinnerTeam(const std::string& teamName);

        ~Renderer();

    private:
        void lockCursor();
        void beginDraw();
        void draw3D();

    private:
        unsigned int m_width;
        unsigned int m_height;
        std::string m_title;

        Chrono m_chrono;
        unsigned int m_timeUnit;
        unsigned int m_tickCount;

        Color m_backgroundColor;

        unsigned int m_tickRate;

        bool m_gameEnd;
        std::string m_winnerTeam;
        shader::Fog m_fogShader;
        Camera m_camera;
        Grid* m_grid;
        Hud m_hud;

        Trantorian* m_focusedPlayer;

        std::vector<std::string> m_teamNames;
        std::vector<sptr<Trantorian>> m_trantorians;
};

}