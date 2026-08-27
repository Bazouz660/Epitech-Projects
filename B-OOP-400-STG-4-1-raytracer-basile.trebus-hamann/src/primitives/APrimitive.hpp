/*
** EPITECH PROJECT, 2023
** B-OOP-400-STG-4-1-raytracer-basile.trebus-hamann
** File description:
** APrimitive
*/


#pragma once

#include "IPrimitive.hpp"

namespace RayTracer {

    class APrimitive : public IPrimitive {

        public:
            virtual ~APrimitive() = default;

            virtual void setColor(const Color::RGB &color) override { m_color = color; }
            virtual const Color::RGB& getColor() const override { return m_color; }
            virtual void setMaterial(const Material &material) override { m_material = material; }
            virtual const Material& getMaterial() const override { return m_material; }

            virtual void setName(const std::string &name) override { m_name = name; }
            virtual std::string getName() const override { return m_name; }

        protected:
            Material m_material;
            Color::RGB m_color;
            std::string m_name = "unnamed";
    };

}