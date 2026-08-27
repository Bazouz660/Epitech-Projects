/*
** EPITECH PROJECT, 2023
** B-OOP-400-STG-4-1-raytracer-basile.trebus-hamann
** File description:
** IPrimitive
*/

#pragma once

#include "Vector3.hpp"
#include "Color.hpp"
#include "Ray.hpp"
#include "AABB.hpp"
#include "Material.hpp"

namespace RayTracer {

    class IPrimitive {

        public:
            virtual ~IPrimitive() = default;

            virtual void translate(const Math::Vector3<double> &translation) = 0;
            virtual void rotate(const Math::Vector3<double> &rotation) = 0;
            virtual void scale(const Math::Vector3<double> &scale) = 0;

            virtual void setColor(const Color::RGB &color) = 0;
            virtual const Color::RGB& getColor() const = 0;

            virtual void setMaterial(const Material &material) = 0;
            virtual const Material& getMaterial() const = 0;

            virtual std::string getName() const = 0;
            virtual void setName(const std::string &name) = 0;

            virtual Space::AABB getBounds() const = 0;

            virtual bool hits(Ray &ray) const = 0;
    };

}