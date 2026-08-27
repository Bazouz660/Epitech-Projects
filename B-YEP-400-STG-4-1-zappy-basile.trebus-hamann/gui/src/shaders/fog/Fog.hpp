/*
** EPITECH PROJECT, 2023
** B-YEP-400-STG-4-1-zappy-basile.trebus-hamann
** File description:
** Fog
*/

#pragma once

#include "common.hpp"

namespace zpy::shader {

    class Fog {

        public:
            Fog();
            ~Fog();

            void init();

            void setDensity(float density);
            float getDensity() const;

            void setColor(const Color &color);
            const Color& getColor() const;

            Shader& getHandle();

        private:
            Shader m_shader;
            bool m_isLoaded = false;
            int m_densityLoc;
            int m_ambientLoc;
            int m_colorLoc;
            float m_density;
            Color m_color;
    };

}