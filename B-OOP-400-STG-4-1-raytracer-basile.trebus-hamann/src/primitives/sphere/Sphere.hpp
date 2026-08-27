/*
** EPITECH PROJECT, 2023
** B-OOP-400-STG-4-1-raytracer-basile.trebus-hamann
** File description:
** Sphere
*/

#pragma once

#include "APrimitive.hpp"

namespace RayTracer {

    class Sphere : public APrimitive {

        public:
            Sphere(const Math::Vector3<double> &center, double radius, const Color::RGB& color = Color::RGB(),
            const std::string &name = "unnamed", const Material& material = Material());
            Sphere(const Sphere &other);
            ~Sphere() override = default;

            double getRadius() const;
            Math::Vector3<double> getCenter() const;

            void translate(const Math::Vector3<double> &translation) override;
            void rotate(const Math::Vector3<double> &rotation) override;
            void scale(const Math::Vector3<double> &scale) override;

            Space::AABB getBounds() const override;

            bool hits(Ray &ray) const override;

        private:
            Math::Vector3<double> m_center;
            double m_radius;
            Math::Vector3<double> m_rotation;
    };

}