/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Cylinder
*/

#ifndef CYLINDER_HPP_
#define CYLINDER_HPP_

#include "APrimitive.hpp"

namespace RayTracer {

    class Cylinder : public APrimitive {
        public:
            Cylinder(const Math::Vector3<double> &center, const Math::Vector3<double> &axis, double height, double radius, const Color::RGB& color,
            const std::string &name = "unnamed", const Material& material = Material());
            Cylinder(const Cylinder &other);
            ~Cylinder() override = default;

            void translate(const Math::Vector3<double> &translation) override;
            void rotate(const Math::Vector3<double> &rotation) override;
            void scale(const Math::Vector3<double> &scale) override;

            Space::AABB getBounds() const override;

            bool hits(Ray &ray) const override;

        private:
            Math::Vector3<double> m_center;
            Math::Vector3<double> m_axis;
            double m_height;
            double m_radius;
            Math::Vector3<double> m_rotation;
    };
}

#endif /* !CYLINDER_HPP_ */
