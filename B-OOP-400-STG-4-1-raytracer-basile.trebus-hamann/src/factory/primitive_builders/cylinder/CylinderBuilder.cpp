/*
** EPITECH PROJECT, 2023
** B-OOP-400-STG-4-1-raytracer-basile.trebus-hamann
** File description:
** CylinderBuilder
*/

#include "CylinderBuilder.hpp"

namespace RayTracer {

    CylinderBuilder &CylinderBuilder::setCenter(double x, double y, double z)
    {
        m_center = Math::Vector3<double>(x, y, z);
        return *this;
    }

    CylinderBuilder &CylinderBuilder::setRadius(double radius)
    {
        m_radius = radius;
        return *this;
    }

    CylinderBuilder &CylinderBuilder::setHeight(double height)
    {
        m_height = height;
        return *this;
    }

    CylinderBuilder &CylinderBuilder::setAxis(double x, double y, double z)
    {
        m_axis = Math::Vector3<double>(x, y, z);
        return *this;
    }

    sptr<IPrimitive> CylinderBuilder::build()
    {
        return std::make_shared<Cylinder>(m_center, m_axis, m_height, m_radius, m_color, m_name, m_material);
    }

}