/*
** EPITECH PROJECT, 2023
** B-OOP-400-STG-4-1-raytracer-basile.trebus-hamann
** File description:
** DirectionalLightBuilder
*/

#pragma once

#include "DirectionalLight.hpp"

namespace RayTracer {

    class DirectionalLightBuilder {
        public:
            DirectionalLightBuilder() = default;
            ~DirectionalLightBuilder() = default;

            DirectionalLightBuilder &setDirection(double x, double y, double z);
            DirectionalLightBuilder &setColor(const Color::RGB &color);
            DirectionalLightBuilder &setIntensity(double intensity);

            sptr<DirectionalLight> build();

        private:
            Math::Vector3<double> m_position = Math::Vector3<double>{0, 0, 0};
            Color::RGB m_color = Color::RGB(255, 255, 255);
            double m_intensity = 1.0;
    };

}