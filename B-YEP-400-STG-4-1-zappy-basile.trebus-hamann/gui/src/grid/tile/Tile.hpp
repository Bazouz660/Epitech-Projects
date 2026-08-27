/*
** EPITECH PROJECT, 2023
** Raylib_test
** File description:
** Tile
*/

#pragma once

#include "common.hpp"
#include "Vec2.hpp"
#include "Vec3.hpp"
#include "Vec4.hpp"
#include "Camera.hpp"

namespace zpy {

    enum Resources {
        FOOD,
        LINEMATE,
        DERAUMERE,
        SIBUR,
        MENDIANE,
        PHIRAS,
        THYSTAME
    };

    class Tile {
        public:
            Tile(Vec2 pos, unsigned int size);
            ~Tile();

            struct resource_s {
                Vec4 localPos;
                Model model;
            };

            void drawResources(Camera& cam, Shader* shader = nullptr);

            void setResource(const Resources& resource, int quantity);
            void addResource(const Resources& resource, int quantity);
            int getRes(const Resources& resource) const;
            void popResource(const Resources& resource);

            const Vec2& getWorldPos() const;

        private:
            Vec2 getRandomPosOnTile() const;

        private:
            std::map<Resources, std::vector<sptr<resource_s>>> m_resources;
            std::map<Resources, sptr<Texture>> m_textureMap;
            Vec2 m_pos;
            unsigned int m_size;
    };

}
