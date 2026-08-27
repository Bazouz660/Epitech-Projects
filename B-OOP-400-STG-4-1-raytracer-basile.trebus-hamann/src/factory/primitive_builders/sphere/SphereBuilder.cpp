/*
** EPITECH PROJECT, 2023
** B-OOP-400-STG-4-1-raytracer-basile.trebus-hamann
** File description:
** SphereBuilder
*/

#include "SphereBuilder.hpp"

namespace RayTracer {

    SphereBuilder &SphereBuilder::setCenter(double x, double y, double z)
    {
        m_center = Math::Vector3<double>(x, y, z);
        return *this;
    }

    SphereBuilder &SphereBuilder::setRadius(double radius)
    {
        m_radius = radius;
        return *this;
    }

    sptr<IPrimitive> SphereBuilder::build()
    {
        return std::make_shared<Sphere>(m_center, m_radius, m_color, m_name, m_material);
    }

}