/*
** EPITECH PROJECT, 2023
** B-OOP-400-STG-4-1-raytracer-basile.trebus-hamann
** File description:
** SphereBuilder
*/

#pragma once

#include "APrimitiveBuilder.hpp"
#include "Sphere.hpp"

namespace RayTracer {

    class SphereBuilder : public APrimitiveBuilder {
        public:
            SphereBuilder() = default;
            virtual ~SphereBuilder() = default;

            SphereBuilder &setCenter(double x, double y, double z);
            SphereBuilder &setRadius(double radius);

            sptr<IPrimitive> build() override;

        private:
            Math::Vector3<double> m_center;
            double m_radius;
    };

}