/*
** EPITECH PROJECT, 2023
** B-OOP-400-STG-4-1-raytracer-basile.trebus-hamann
** File description:
** PointLightBuilder
*/

#pragma once

#include "PointLight.hpp"

namespace RayTracer {

    class PointLightBuilder {
        public:
            PointLightBuilder() = default;
            ~PointLightBuilder() = default;

            PointLightBuilder &setPosition(double x, double y, double z);
            PointLightBuilder &setColor(const Color::RGB &color);
            PointLightBuilder &setIntensity(double intensity);
            PointLightBuilder &setRadius(double radius);
            PointLightBuilder &setFalloff(double falloff);

            sptr<PointLight> build();

        private:
            Math::Vector3<double> m_position = Math::Vector3<double>(0, 0, 0);
            Color::RGB m_color = Color::RGB(255, 255, 255);
            double m_intensity = 1;
            double m_radius = 1;
            double m_falloff = 1;
    };

}