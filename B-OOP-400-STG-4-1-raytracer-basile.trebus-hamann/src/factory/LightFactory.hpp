/*
** EPITECH PROJECT, 2023
** B-OOP-400-STG-4-1-raytracer-basile.trebus-hamann
** File description:
** LightFactory
*/

#pragma once

#include "DirectionalLightBuilder.hpp"
#include "PointLightBuilder.hpp"
//#include "SpotLightBuilder.hpp"

namespace RayTracer {

    class LightFactory {
        public:
            LightFactory() = default;
            ~LightFactory() = default;

            static sptr<DirectionalLightBuilder> createDirectional() { return std::make_shared<DirectionalLightBuilder>(); }
            static sptr<PointLightBuilder> createPoint() { return std::make_shared<PointLightBuilder>(); }
    };

}