/*
** EPITECH PROJECT, 2023
** B-OOP-400-STG-4-1-raytracer-basile.trebus-hamann
** File description:
** APrimitiveBuilder
*/

#pragma once

#include "IPrimitiveBuilder.hpp"

namespace RayTracer {

    class APrimitiveBuilder : public IPrimitiveBuilder {
        public:
            APrimitiveBuilder() = default;
            virtual ~APrimitiveBuilder() = default;

            virtual IPrimitiveBuilder &setColor(const Color::RGB &color) override { m_color = color; return *this; }
            virtual IPrimitiveBuilder &setName(const std::string &name) override { m_name = name; return *this; }
            virtual IPrimitiveBuilder &setMaterial(const Material& material) override { m_material = material; return *this; }

        protected:
            Color::RGB m_color;
            Material m_material;
            std::string m_name = "unnamed";
    };

}