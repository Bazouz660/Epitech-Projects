/*
** EPITECH PROJECT, 2023
** Raylib_test
** File description:
** Grid
*/

#include "Grid.hpp"
#include "ResourceManager.hpp"
#include "unistd.h"
#include "string.h"

namespace zpy {

Grid::Grid(const unsigned int &tileSize, Camera& cam)
    : m_cam(cam)
{
    m_dimension = {5, 5};
    m_tileSize = tileSize;
    m_rdy = false;
}

Grid::~Grid()
{
}

void Grid::init()
{
    genMesh();

    setPosition(Vec3(0 - m_dimension.x / 2 , 0.5, 0 - m_dimension.y / 2));

    for (int i = 0; i < m_dimension.x * m_dimension.y; i++) {
        Vec2 pos;
        pos.x = (float(i % (int)m_dimension.x) * m_tileSize) - (m_dimension.x / 2);
        pos.y = (float(i / (int)m_dimension.x) * m_tileSize) - (m_dimension.y / 2);
        m_tiles.push_back(std::make_shared<Tile>(pos, m_tileSize));
    }

    m_rdy = true;
}

bool Grid::isReady() const
{
    return m_rdy;
}

void Grid::genMesh()
{
    Image image;

    image.format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8;
    image.width = m_dimension.x;
    image.height = m_dimension.y;
    image.data = (unsigned char *)RL_MALLOC(m_dimension.x * m_dimension.y * 4);
    image.data = memset(image.data, 255, m_dimension.x * m_dimension.y * 4);
    image.mipmaps = 4;

    Mesh mesh = GenMeshCubicmap(image, Vec3(1.0f, 1.0f, 1.0f));

    m_model = LoadModelFromMesh(mesh);

    Texture& texture = *getResource().getTexture("grass");

    SetTextureFilter(texture, TEXTURE_FILTER_ANISOTROPIC_16X);

    m_model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;

    m_position = { -(float)(m_dimension.x / 2), 0.0f, -(float)(m_dimension.y / 2) };

    UnloadImage(image);
}

Model& Grid::getModel()
{
    return m_model;
}

void Grid::draw(Shader* shader)
{
    if (!m_rdy)
        return;
    //drawInstanced();
    //drawIterative();

    for (auto& tile : m_tiles)
        tile->drawResources(m_cam, shader);

    if (shader != nullptr) {
        m_model.materials[0].shader = *shader;
    }

    DrawModel(m_model, m_position, 1.0f, WHITE);
}

const Vec3& Grid::getPosition() const
{
    return m_position;
}

const Vec2& Grid::getDimension() const
{
    return m_dimension;
}

void Grid::setDimension(const Vec2 &dimension)
{
    m_dimension = dimension;
}

void Grid::setPosition(const Vec3 &position)
{
    m_position = position;
}

Tile& Grid::getTile(const Vec2 &pos)
{
    if (m_tiles.size() <= pos.y * m_dimension.x + pos.x)
        throw std::out_of_range("Tile out of range");
    sptr<Tile> tile = m_tiles.at(pos.y * m_dimension.x + pos.x);
    if (tile == nullptr)
        throw std::out_of_range("Tile out of range");
    return *tile;
}

}
