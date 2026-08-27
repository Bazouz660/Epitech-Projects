/*
** EPITECH PROJECT, 2023
** B-OOP-400-STG-4-1-raytracer-basile.trebus-hamann
** File description:
** Triangle
*/

#pragma once

#include "APrimitive.hpp"

namespace RayTracer {

    class Triangle : public APrimitive {

        public:
            Triangle(const Math::Vector3<double> a, const Math::Vector3<double> b, const Math::Vector3<double> c,
                const Math::Vector3<double> nA, const Math::Vector3<double> nB, const Math::Vector3<double> nC,
                const Color::RGB& color = Color::RGB(), const std::string &name = "unnamed", const Material& material = Material());

            Triangle(const Triangle &other);
            ~Triangle() override = default;

            void translate(const Math::Vector3<double> &translation) override;
            void rotate(const Math::Vector3<double> &rotation) override;
            void scale(const Math::Vector3<double> &scale) override;

            Space::AABB getBounds() const override;

            bool hits(Ray &ray) const override;

        private:
            Math::Vector3<double> getNormal() const;

        private:
            Math::Vector3<double> m_a;
            Math::Vector3<double> m_b;
            Math::Vector3<double> m_c;

            Math::Vector3<double> m_nA;
            Math::Vector3<double> m_nB;
            Math::Vector3<double> m_nC;
    };

}