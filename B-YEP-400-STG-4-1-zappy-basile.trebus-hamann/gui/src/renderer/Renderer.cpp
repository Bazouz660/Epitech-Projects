/*
** EPITECH PROJECT, 2023
** B-YEP-400-STG-4-1-zappy-basile.trebus-hamann
** File description:
** Renderer
*/

#include "Renderer.hpp"
#include "Vec2.hpp"
#include "Vec3.hpp"
#include "ResourceManager.hpp"
#include "context.hpp"
#include "utils.hpp"
#include <fstream>

namespace zpy {

Renderer::Renderer(unsigned int width, unsigned int height, const std::string &title)
: m_camera(70), m_focusedPlayer(nullptr)
{
    context::setRenderer(*this);
    m_width = width;
    m_height = height;
    m_title = title;
    m_gameEnd = false;
    m_winnerTeam = "";
}

void Renderer::init(unsigned int tickRate)
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
    InitWindow(m_width, m_height, m_title.c_str());
    SetWindowPosition((GetMonitorWidth(0) / 4), GetMonitorHeight(0) / 4);

    context::setCamera(m_camera);

    try {
        ResourceManager::getInstance().loadResources();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        ResourceManager::getInstance().unloadAll();
        std::exit(84);
    }

    m_fogShader.init();
    m_fogShader.setDensity(0.05f);

    m_tickRate = tickRate;
    m_backgroundColor = {70, 70, 70, 255};

    if (m_tickRate > 0)
        SetTargetFPS(m_tickRate);

    m_grid = new Grid(1, m_camera);
    m_chrono.start();
}

void Renderer::update()
{
    for (auto& player : m_trantorians) {
        player->update();
    }
    updateHudFocusedPlayer();
    m_hud.update();
    if (!(IsKeyDown(KEY_LEFT_CONTROL) || !IsWindowFocused() || IsWindowMinimized()
        || IsWindowHidden() || !IsCursorOnScreen())) {
        m_camera.update();
        lockCursor();
        HideCursor();
    } else
        ShowCursor();
    Shader& shader = m_fogShader.getHandle();
    SetShaderValue(shader, shader.locs[SHADER_LOC_VECTOR_VIEW], &m_camera.getPosition().x, SHADER_UNIFORM_VEC3);
}

void Renderer::handleEvents()
{
    if (IsWindowResized()) {
        updateHudInfo();
    }
    if (IsKeyPressed(KEY_F11))
        ToggleFullscreen();
}

void Renderer::draw3D()
{
    BeginMode3D(m_camera.get());

    m_grid->draw(&m_fogShader.getHandle());

    for (auto& player : m_trantorians) {
        player->draw(&m_fogShader.getHandle());
    }

    EndMode3D();
}

Grid& Renderer::getGrid() const
{
    return *m_grid;
}

Camera& Renderer::getCamera()
{
    return m_camera;
}

Vec2 Renderer::getWindowSize()
{
    return Vec2(static_cast<float>(GetScreenWidth()), static_cast<float>(GetScreenHeight()));
}

void Renderer::setFocusedPlayer(Trantorian *player)
{
    m_focusedPlayer = player;
    updateHudInfo();
}

void Renderer::updateHudFocusedPlayer()
{
    int fontSize = 20;

    if (!m_focusedPlayer) {
        m_hud.addText("PlayerName", std::make_shared<Hud::Text>("No player selected", Vec2(10, fontSize * 2), fontSize * 0.8, WHITE));
        m_hud.removeText("PlayerLevel");
        m_hud.removeText("PlayerInventory");
        m_hud.removeText("PlayerFood");
        m_hud.removeText("PlayerLinemate");
        m_hud.removeText("PlayerDeraumere");
        m_hud.removeText("PlayerSibur");
        m_hud.removeText("PlayerMendiane");
        m_hud.removeText("PlayerPhiras");
        m_hud.removeText("PlayerThystame");
    } else {
        m_hud.addText("PlayerName", std::make_shared<Hud::Text>("ID[" + std::to_string(m_focusedPlayer->getId()) + "] Team: " + m_focusedPlayer->getTeamName(), Vec2(10, fontSize * 2), fontSize * 0.8, WHITE));
        m_hud.addText("PlayerLevel", std::make_shared<Hud::Text>("Level: " + std::to_string(m_focusedPlayer->getLevel()), Vec2(10, fontSize * 3), fontSize * 0.8, WHITE));
        m_hud.addText("PlayerInventory", std::make_shared<Hud::Text>("Inventory:", Vec2(10, fontSize * 4), fontSize * 0.8, WHITE));
        m_hud.addText("PlayerFood", std::make_shared<Hud::Text>("Food: " + std::to_string(m_focusedPlayer->getInventory().getFood()), Vec2(10, fontSize * 5), fontSize * 0.8, WHITE));
        m_hud.addText("PlayerLinemate", std::make_shared<Hud::Text>("Linemate: " + std::to_string(m_focusedPlayer->getInventory().getLinemate()), Vec2(10, fontSize * 6), fontSize * 0.8, WHITE));
        m_hud.addText("PlayerDeraumere", std::make_shared<Hud::Text>("Deraumere: " + std::to_string(m_focusedPlayer->getInventory().getDeraumere()), Vec2(10, fontSize * 7), fontSize * 0.8, WHITE));
        m_hud.addText("PlayerSibur", std::make_shared<Hud::Text>("Sibur: " + std::to_string(m_focusedPlayer->getInventory().getSibur()), Vec2(10, fontSize * 8), fontSize * 0.8, WHITE));
        m_hud.addText("PlayerMendiane", std::make_shared<Hud::Text>("Mendiane: " + std::to_string(m_focusedPlayer->getInventory().getMendiane()), Vec2(10, fontSize * 9), fontSize * 0.8, WHITE));
        m_hud.addText("PlayerPhiras", std::make_shared<Hud::Text>("Phiras: " + std::to_string(m_focusedPlayer->getInventory().getPhiras()), Vec2(10, fontSize * 10), fontSize * 0.8, WHITE));
        m_hud.addText("PlayerThystame", std::make_shared<Hud::Text>("Thystame: " + std::to_string(m_focusedPlayer->getInventory().getThystame()), Vec2(10, fontSize * 11), fontSize * 0.8, WHITE));
    }
}

void Renderer::updateHudInfo()
{
    int i = 0;
    int fontSize = 20;

    Vec2 wSize = getWindowSize();

    int maxWidth = 0;
    for (auto& team : m_teamNames) {
        int width = MeasureText(team.c_str(), fontSize);
        if (width > maxWidth)
            maxWidth = width;
        i++;
    }
    maxWidth += 40;

    if (m_winnerTeam != "") {
        std::string msg = "Game ended: Team[" + m_winnerTeam + "] won";
        m_hud.addText("GameEnd", std::make_shared<Hud::Text>(msg, Vec2(wSize.x / 2 - MeasureText(msg.c_str(), fontSize * 1.5) / 2, wSize.y / 4 - (fontSize * 1.5) / 2), (fontSize * 1.5), ORANGE));
    }

    Rectangle rect = {wSize.x - maxWidth, 0, (float)maxWidth, wSize.y};
    m_hud.addRect("teamsBg", std::make_shared<Rectangle>(rect));

    Rectangle rect2 = {0, 0, 250, 250};
    m_hud.addRect("playerInfoRect", std::make_shared<Rectangle>(rect2));

    m_hud.addText("teams", std::make_shared<Hud::Text>("Teams:", Vec2(rect.x + 20, rect.y + 10), fontSize, WHITE));
    m_hud.addText("playerInfo", std::make_shared<Hud::Text>("Player info:", Vec2(10, 10), fontSize, WHITE));

    for (auto& team : m_teamNames) {
        m_hud.addText(team + "Text", std::make_shared<Hud::Text>(team, Vec2(rect.x + 20, rect.y + 10 + (i * 30)), fontSize, context::getTeamColor(team)));
        i++;
    }
}

void Renderer::beginDraw()
{
    BeginDrawing();
    ClearBackground(m_backgroundColor);
}

void Renderer::draw()
{
    beginDraw();

    draw3D();

    m_hud.draw();

    EndDrawing();
}

void Renderer::setWinnerTeam(const std::string &teamName)
{
    m_winnerTeam = teamName;
    m_gameEnd = true;
}

void Renderer::addTeam(const std::string &teamName)
{
    for (auto& team : m_teamNames) {
        if (team == teamName)
            throw std::runtime_error("Team already exists");
    }

    context::addTeamColor(teamName, utils::getRandomColor());
    m_teamNames.push_back(teamName);
    std::cerr << "Added team " << teamName << std::endl;
}

void Renderer::addPlayer(const Vec2 &pos, Trantorian::Orientation orientation,
    unsigned int level, int id, std::string teamName)
{
    m_trantorians.push_back(std::make_shared<Trantorian>(pos, orientation, level, id, teamName, *m_grid));
}

std::vector<sptr<Trantorian>>& Renderer::getPlayers()
{
    return m_trantorians;
}

sptr<Trantorian> Renderer::getPlayer(int id)
{
    for (auto& player : m_trantorians) {
        if (player->getId() == id)
            return player;
    }
    return nullptr;
}

void Renderer::lockCursor()
{
    SetMousePosition(GetScreenWidth() / 2, GetScreenHeight() / 2);
}

bool Renderer::shouldClose() const
{
    return WindowShouldClose();
}

void Renderer::close()
{
    delete m_grid;
    m_fogShader.~Fog();
    ResourceManager::getInstance().unloadAll();
}

void Renderer::setTimeUnit(unsigned int timeUnit)
{
    m_timeUnit = timeUnit;
}

void Renderer::incrementTick()
{
    m_tickCount++;
}

unsigned int Renderer::getTickCount() const
{
    return m_tickCount;
}

void Renderer::setTickCount(unsigned int tickCount)
{
    m_tickCount = tickCount;
}

Renderer::~Renderer()
{
    close();
    CloseWindow();
}

}
