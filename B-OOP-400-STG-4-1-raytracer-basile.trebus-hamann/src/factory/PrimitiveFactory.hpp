/*
** EPITECH PROJECT, 2023
** B-OOP-400-STG-4-1-raytracer-basile.trebus-hamann
** File description:
** PrimitiveFactory
*/

#pragma once

// builder factory

#include "SphereBuilder.hpp"
#include "PlaneBuilder.hpp"
#include "CylinderBuilder.hpp"
#include "TriangleBuilder.hpp"

namespace RayTracer {

    class PrimitiveFactory {
        public:
            PrimitiveFactory() = default;
            ~PrimitiveFactory() = default;

            static sptr<SphereBuilder> createSphere() { return std::make_shared<SphereBuilder>(); }
            static sptr<PlaneBuilder> createPlane() { return std::make_shared<PlaneBuilder>(); }
            static sptr<CylinderBuilder> createCylinder() { return std::make_shared<CylinderBuilder>(); }
            static sptr<TriangleBuilder> createTriangle() { return std::make_shared<TriangleBuilder>(); }
    };

}