/*
** EPITECH PROJECT, 2023
** B-OOP-400-STG-4-1-raytracer-basile.trebus-hamann
** File description:
** DirectionalLightBuilder
*/

#include "DirectionalLightBuilder.hpp"

namespace RayTracer {

    DirectionalLightBuilder &DirectionalLightBuilder::setDirection(double x, double y, double z)
    {
        m_position = Math::Vector3<double>(x, y, z);
        return *this;
    }

    DirectionalLightBuilder &DirectionalLightBuilder::setColor(const Color::RGB &color)
    {
        m_color = color;
        return *this;
    }

    DirectionalLightBuilder &DirectionalLightBuilder::setIntensity(double intensity)
    {
        m_intensity = intensity;
        return *this;
    }

    sptr<DirectionalLight> DirectionalLightBuilder::build()
    {
        return std::make_shared<DirectionalLight>(m_position, m_color, m_intensity);
    }

}