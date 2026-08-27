/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** ILight
*/

#pragma once

#include "IPrimitive.hpp"
#include "Ray.hpp"

namespace RayTracer {

    class ILight {

        public:
            virtual ~ILight() = default;

            virtual void setIntensity(double intensity) = 0;
            virtual void setColor(const Color::RGB &color) = 0;
            virtual void setPosition(const Math::Vector3<double> &position) = 0;

            virtual double getIntensity() const = 0;
            virtual const Color::RGB& getColor() const = 0;
            virtual Math::Vector3<double> getPosition() const = 0;

            virtual bool computeDropShadow(Ray& hitRay, IPrimitive& obj,
                std::vector<sptr<IPrimitive>> objs) const = 0;
            virtual void computeDiffuse(Ray& hitRay, IPrimitive& obj) const = 0;
            virtual void computeSpecular(Ray& hitRay, IPrimitive& obj) const = 0;
    };
}
