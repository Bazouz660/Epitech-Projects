/*
** EPITECH PROJECT, 2023
** Raylib_test
** File description:
** Tile
*/

#include "Tile.hpp"
#include "ResourceManager.hpp"

namespace zpy {

    Tile::Tile(Vec2 pos, unsigned int size)
        : m_pos(pos), m_size(size)
    {
        m_resources[Resources::FOOD].resize(0);
        m_resources[Resources::LINEMATE].resize(0);
        m_resources[Resources::DERAUMERE].resize(0);
        m_resources[Resources::SIBUR].resize(0);
        m_resources[Resources::MENDIANE].resize(0);
        m_resources[Resources::PHIRAS].resize(0);
        m_resources[Resources::THYSTAME].resize(0);

        m_textureMap[Resources::FOOD] = getResource().getTexture("apple");
        m_textureMap[Resources::LINEMATE] = getResource().getTexture("lapis");
        m_textureMap[Resources::DERAUMERE] = getResource().getTexture("iron");
        m_textureMap[Resources::SIBUR] = getResource().getTexture("redstone");
        m_textureMap[Resources::MENDIANE] = getResource().getTexture("gold");
        m_textureMap[Resources::PHIRAS] = getResource().getTexture("diamond");
        m_textureMap[Resources::THYSTAME] = getResource().getTexture("emerald");
    }

    Tile::~Tile()
    {
    }

    const Vec2& Tile::getWorldPos() const
    {
        return m_pos;
    }

    // Return a random position on the tile
    Vec2 Tile::getRandomPosOnTile() const
    {
        float x = m_pos.x;
        float y = m_pos.y;

        float halfSize = (m_size * 100) / 2;

        x += GetRandomValue(-halfSize, halfSize) / 100.f;
        y += GetRandomValue(-halfSize, halfSize) / 100.f;

        return Vec2(x, y);
    }

    void Tile::setResource(const Resources& resource, int value)
    {
        int diff = value - m_resources[resource].size();

        if (diff > 0)
            addResource(resource, diff);
        else if (diff < 0)
            for (int i = 0; i < -diff; i++)
                popResource(resource);
    }

    void Tile::addResource(const Resources& type, int value)
    {
        for (int i = 0; i < value; i++) {
            Vec2 tilepos = getRandomPosOnTile();
            Vec4 pos = {tilepos.x, 1.8f, tilepos.y, (float)GetRandomValue(0, 5000) / 1000.f};
            pos.w *= (float)GetRandomValue(-100, 100) / 100.f;
            resource_s res;
            res.localPos = pos;
            res.model = LoadModelFromMesh(GenMeshCube(1.f, 1.f, 1.f));
            res.model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = *m_textureMap[type];
            m_resources.at(type).push_back(std::make_shared<resource_s>(res));
        }
    }

    int Tile::getRes(const Resources& type) const
    {
        return m_resources.at(type).size();
    }

    void Tile::popResource(const Resources& resource)
    {
        if (m_resources[resource].size() <= 0)
            throw std::runtime_error("Error: resource is empty");

        m_resources[resource].erase(m_resources[resource].begin() + rand() % m_resources[resource].size());
    }

    void Tile::drawResources(Camera& cam, Shader* shader)
    {
        static float rotation = 0.f * PI;

        rotation = (GetTime() * PI) * 10.f;

        for (auto& [type, vect] : m_resources) {
            for (auto& resource : vect) {
                Vec4 pos = resource->localPos;
                if (shader) {
                    resource->model.materials[0].shader = *shader;
                }
                pos.y = std::cos((GetTime() + pos.w) * 2.f) * 0.1f + 1.8f;
                if (type == FOOD) {
                    BeginShaderMode(*shader);
                    DrawBillboard(cam.get(), *m_textureMap[type], Vec3(pos.x, pos.y, pos.z), 0.2f, WHITE);
                    EndShaderMode();
                } else
                    DrawModelEx(resource->model, Vec3(pos.x, pos.y, pos.z), {0.f, 1.f, 0.f}, rotation, {0.2f, 0.2f, 0.2f}, WHITE);
            }
        }
    }

}