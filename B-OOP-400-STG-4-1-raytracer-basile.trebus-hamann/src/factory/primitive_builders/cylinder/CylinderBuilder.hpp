/*
** EPITECH PROJECT, 2023
** B-OOP-400-STG-4-1-raytracer-basile.trebus-hamann
** File description:
** CylinderBuilder
*/

#pragma once

#include "APrimitiveBuilder.hpp"
#include "Cylinder.hpp"

namespace RayTracer {

    class CylinderBuilder : public APrimitiveBuilder {
        public:
            CylinderBuilder() = default;
            virtual ~CylinderBuilder() = default;

            CylinderBuilder &setCenter(double x, double y, double z);
            CylinderBuilder &setRadius(double radius);
            CylinderBuilder &setHeight(double height);
            CylinderBuilder &setAxis(double x, double y, double z);

            sptr<IPrimitive> build() override;

        private:
            Math::Vector3<double> m_center = {0, 0, 0};
            Math::Vector3<double> m_axis = {0, 1, 0};
            double m_height = 1;
            double m_radius = 1;
    };

}