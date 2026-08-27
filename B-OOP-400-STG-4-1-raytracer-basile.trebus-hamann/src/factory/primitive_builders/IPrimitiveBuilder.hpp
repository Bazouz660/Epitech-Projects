/*
** EPITECH PROJECT, 2023
** B-OOP-400-STG-4-1-raytracer-basile.trebus-hamann
** File description:
** IPrimitiveBuilder
*/

#pragma once

#include "common.hpp"
#include "IPrimitive.hpp"

namespace RayTracer {

    class IPrimitiveBuilder {
        public:
            virtual ~IPrimitiveBuilder() = default;

            virtual IPrimitiveBuilder &setColor(const Color::RGB &color) = 0;
            virtual IPrimitiveBuilder &setName(const std::string &name) = 0;
            virtual IPrimitiveBuilder &setMaterial(const Material& material) = 0;

            virtual sptr<IPrimitive> build() = 0;
    };

}