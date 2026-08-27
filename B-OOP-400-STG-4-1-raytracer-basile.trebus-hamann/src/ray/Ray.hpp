/*
** EPITECH PROJECT, 2023
** B-OOP-400-STG-4-1-raytracer-basile.trebus-hamann
** File description:
** Ray
*/

#pragma once

#include "Vector3.hpp"
#include "Color.hpp"

namespace RayTracer {

    class IPrimitive;
    class ILight;

    class Ray {

        public:
            typedef struct light_info_s
            {
                Color::RGB pointColor;
                bool isShadowed;
            } light_info_t;

            typedef struct hit_s
            {
                double dist = std::numeric_limits<double>::max();
                Math::Vector3<double> hitPosition;
                Math::Vector3<double> normal;
                IPrimitive *obj = nullptr;
                std::map<ILight *,sptr<light_info_t>> lights_info;
            } hit_t;


            Math::Vector3<double> origin;
            Math::Vector3<double> dir;
            Color::RGB m_finalColor;

            Ray();
            Ray(const Math::Vector3<double> &origin, const Math::Vector3<double> &direction);
            Ray(const Ray &other);
            Ray(Ray &&other) noexcept;

            hit_t& getHit();
            hit_t& getClosestHit();

            Ray &operator=(const Ray &other);
            Ray &operator=(Ray &&other) noexcept;

        private:
            hit_t m_hit;
            hit_t m_closestHit;
    };

}