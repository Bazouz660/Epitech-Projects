/*
** EPITECH PROJECT, 2023
** Raylib_test
** File description:
** Grid
*/

#pragma once

#include "common.hpp"
#include "Tile.hpp"
#include "Vec2.hpp"
#include "Vec3.hpp"
#include "Camera.hpp"

namespace zpy {

class Grid {
    public:
        Grid(const unsigned int& tileSize, Camera& cam);
        ~Grid();

        void init();
        bool isReady() const;

        Model& getModel();

        void draw(Shader* shader = nullptr);

        const Vec2& getDimension() const;
        void setDimension(const Vec2 &dimension);

        const Vec3& getPosition() const;
        void setPosition(const Vec3 &position);

        Tile& getTile(const Vec2& index);

    private:
        void genMesh();

    private:
        bool m_shouldUpdateMesh = true;
        bool m_rdy = false;
        unsigned int m_tileSize = 1;
        Vec2 m_dimension = {0, 0};
        Vec3 m_position = {0, 0, 0};
        std::vector<sptr<Tile>> m_tiles;
        Material m_material;
        Model m_model;
        Camera& m_cam;
};

}
