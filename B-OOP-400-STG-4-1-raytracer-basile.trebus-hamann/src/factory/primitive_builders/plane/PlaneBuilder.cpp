/*
** EPITECH PROJECT, 2023
** B-OOP-400-STG-4-1-raytracer-basile.trebus-hamann
** File description:
** PlaneBuilder
*/

#include "PlaneBuilder.hpp"

namespace RayTracer {

    PlaneBuilder &PlaneBuilder::setOrigin(double x, double y, double z)
    {
        m_origin = Math::Vector3<double>(x, y, z);
        return *this;
    }

    PlaneBuilder &PlaneBuilder::setNormal(double x, double y, double z)
    {
        m_normal = Math::Vector3<double>(x, y, z);
        return *this;
    }

    sptr<IPrimitive> PlaneBuilder::build()
    {
        return std::make_shared<Plane>(m_normal, m_origin, m_color, m_name, m_material);
    }

}