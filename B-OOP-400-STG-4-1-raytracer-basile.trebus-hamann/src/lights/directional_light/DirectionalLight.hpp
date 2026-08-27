/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** DirectionalLight
*/

#pragma once

#include "ALight.hpp"

namespace RayTracer {

    class DirectionalLight : public ALight {
        public:
            DirectionalLight(const Math::Vector3<double> &position = Math::Vector3(1.0, -1.0, 1.0),
                const Color::RGB &color = Color::RGB(255, 255, 255), double intensity = 0.5);
            virtual ~DirectionalLight() = default;

            virtual void computeSpecular(Ray& hitRay, IPrimitive& obj) const override final;
            virtual bool computeDropShadow(Ray& hitRay, IPrimitive& obj,
                std::vector<sptr<IPrimitive>> objs) const override final;
            virtual void computeDiffuse(Ray& hitRay, IPrimitive& obj) const override final;
    };
}
