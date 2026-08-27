/*
** EPITECH PROJECT, 2023
** B-OOP-400-STG-4-1-raytracer-basile.trebus-hamann
** File description:
** PointLight
*/

#pragma once

#include "ALight.hpp"

namespace RayTracer {

    class PointLight : public ALight {
        public:
            PointLight(const Math::Vector3<double> &position, double radius = 1.0, double falloff = 2.0,
                const Color::RGB &color = Color::RGB(255, 255, 255), double intensity = 0.5);
            virtual ~PointLight() = default;

            virtual void computeSpecular(Ray& hitRay, IPrimitive& obj) const override final;
            virtual bool computeDropShadow(Ray& hitRay, IPrimitive& obj, std::vector<sptr<IPrimitive>> objs) const override final;
            virtual void computeDiffuse(Ray& hitRay, IPrimitive& obj) const override final;

        private:
            double m_radius;
            double m_falloff;
    };
}
