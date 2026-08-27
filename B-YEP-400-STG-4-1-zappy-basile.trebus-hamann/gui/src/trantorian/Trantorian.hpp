/*
** EPITECH PROJECT, 2023
** B-YEP-400-STG-4-1-zappy-basile.trebus-hamann
** File description:
** Trantorian
*/

#pragma once

#include "common.hpp"
#include "Vec2.hpp"
#include "Inventory.hpp"
#include "Button3d.hpp"

namespace zpy {

    class Grid;

    class Trantorian {
        public:
            enum Orientation {
                NORTH,
                EAST,
                SOUTH,
                WEST
            };
            Trantorian(const Vec2& pos, Orientation orirentation,
                unsigned int level, int id, std::string teamName, Grid& grid);
            ~Trantorian();

            void update();
            void setPos(const Vec2& pos);
            void setOrientation(Orientation orientation);
            void setLevel(unsigned int level);
            void setTeamName(std::string teamName);
            void setId(int id);

            Vec2 getPos() const;
            Orientation getOrientation() const;
            unsigned int getLevel() const;
            std::string getTeamName() const;
            int getId() const;

            Inventory& getInventory();

            void draw(Shader* shader = nullptr);

        private:
            Vec2 m_pos;
            Orientation m_orientation;
            unsigned int m_level;
            int m_id;
            float m_rotation;
            std::string m_teamName;

            Inventory m_inventory;
            Grid& m_grid;
            Button3d m_button;
            Model m_model;
    };

}