/*
** EPITECH PROJECT, 2023
** B-YEP-400-STG-4-1-zappy-basile.trebus-hamann
** File description:
** Inventory
*/

#pragma once

#include "common.hpp"

namespace zpy {

    class Inventory {
        public:
            Inventory() = default;
            ~Inventory() = default;

            void setFood(unsigned int food) { m_food = food; }
            void setLinemate(unsigned int linemate) { m_linemate = linemate; }
            void setDeraumere(unsigned int deraumere) { m_deraumere = deraumere; }
            void setSibur(unsigned int sibur) { m_sibur = sibur; }
            void setMendiane(unsigned int mendiane) { m_mendiane = mendiane; }
            void setPhiras(unsigned int phiras) { m_phiras = phiras; }
            void setThystame(unsigned int thystame) { m_thystame = thystame; }

            unsigned int getFood() const { return m_food; }
            unsigned int getLinemate() const { return m_linemate; }
            unsigned int getDeraumere() const { return m_deraumere; }
            unsigned int getSibur() const { return m_sibur; }
            unsigned int getMendiane() const { return m_mendiane; }
            unsigned int getPhiras() const { return m_phiras; }
            unsigned int getThystame() const { return m_thystame; }

        private:
            unsigned int m_food = 0;
            unsigned int m_linemate = 0;
            unsigned int m_deraumere = 0;
            unsigned int m_sibur = 0;
            unsigned int m_mendiane = 0;
            unsigned int m_phiras = 0;
            unsigned int m_thystame = 0;
    };

}
