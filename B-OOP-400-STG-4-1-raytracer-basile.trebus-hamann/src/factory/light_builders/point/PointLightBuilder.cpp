/*
** EPITECH PROJECT, 2023
** B-OOP-400-STG-4-1-raytracer-basile.trebus-hamann
** File description:
** PointLightBuilder
*/

#include "PointLightBuilder.hpp"

namespace RayTracer {

    PointLightBuilder &PointLightBuilder::setPosition(double x, double y, double z)
    {
        m_position = Math::Vector3<double>(x, y, z);
        return *this;
    }

    PointLightBuilder &PointLightBuilder::setColor(const Color::RGB &color)
    {
        m_color = color;
        return *this;
    }

    PointLightBuilder &PointLightBuilder::setIntensity(double intensity)
    {
        m_intensity = intensity;
        return *this;
    }

    PointLightBuilder &PointLightBuilder::setRadius(double radius)
    {
        m_radius = radius;
        return *this;
    }

    PointLightBuilder &PointLightBuilder::setFalloff(double falloff)
    {
        m_falloff = falloff;
        return *this;
    }

    sptr<PointLight> PointLightBuilder::build()
    {
        return std::make_shared<PointLight>(m_position, m_radius, m_falloff, m_color, m_intensity);
    }

}