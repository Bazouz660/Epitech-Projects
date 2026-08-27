/*
** EPITECH PROJECT, 2023
** B-OOP-400-STG-4-1-raytracer-basile.trebus-hamann
** File description:
** Plane
*/

#pragma once

#include "APrimitive.hpp"

namespace RayTracer {

    class Plane : public APrimitive {
        public:
            Plane(const Math::Vector3<double> &normal, const Math::Vector3<double> &rdPoint,
            const Color::RGB &color, const std::string &name = "unnamed", const Material &material = Material());
            Plane(const Plane &other);
            ~Plane() override = default;

            void translate(const Math::Vector3<double> &translation) override;
            void rotate(const Math::Vector3<double> &rotation) override;
            void scale(const Math::Vector3<double> &scale) override;

            Space::AABB getBounds() const override;

            bool hits(Ray &ray) const;

            Plane &operator=(const Plane &other);
            Plane &operator=(Plane &&other) noexcept;

        private:
            Math::Vector3<double> m_normal;
            Math::Vector3<double> m_rdPoint;
    };

}