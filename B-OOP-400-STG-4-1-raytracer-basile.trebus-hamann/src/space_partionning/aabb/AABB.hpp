/*
** EPITECH PROJECT, 2023
** B-OOP-400-STG-4-1-raytracer-basile.trebus-hamann
** File description:
** AABB
*/

#pragma once

#include "common.hpp"
#include "Ray.hpp"

namespace RayTracer::Space {

    class AABB {
        public:
            AABB();
            AABB(const Math::Vector3<double> &min, const Math::Vector3<double> &max);
            ~AABB() = default;

            bool hits(Ray &ray) const;

            bool contains(const Math::Vector3<double> &point) const;
            bool contains(const AABB &other) const;
            bool intersects(const AABB &other) const;

            const Math::Vector3<double> &getMin() const;
            const Math::Vector3<double> &getMax() const;
            const Math::Vector3<double> getCenter() const;

            void setMin(const Math::Vector3<double> &min);
            void setMax(const Math::Vector3<double> &max);

        private:
            Math::Vector3<double> m_min;
            Math::Vector3<double> m_max;
    };

}
