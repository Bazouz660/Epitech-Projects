/*
** EPITECH PROJECT, 2023
** B-OOP-400-STG-4-1-raytracer-basile.trebus-hamann
** File description:
** PlaneBuilder
*/

#pragma once

#include "APrimitiveBuilder.hpp"
#include "Plane.hpp"

namespace RayTracer {

    class PlaneBuilder : public APrimitiveBuilder {
        public:
            PlaneBuilder() = default;
            virtual ~PlaneBuilder() = default;

            PlaneBuilder &setOrigin(double x, double y, double z);
            PlaneBuilder &setNormal(double x, double y, double z);

            sptr<IPrimitive> build() override;

        private:
            Math::Vector3<double> m_origin;
            Math::Vector3<double> m_normal;
    };

}