/*
** EPITECH PROJECT, 2023
** B-OOP-400-STG-4-1-raytracer-basile.trebus-hamann
** File description:
** transform
*/

#pragma once

#include "Vector3.hpp"

namespace Transform
{
    class Transform
    {
        public:
            Transform();
            ~Transform() = default;

            template<typename T>
            Math::Vector3<T> rotate(const Math::Vector3<T> &point, const Math::Vector3<T> &rotation) const
            {
                Math::Vector3<T> result = point;
                result.x = point.x * cos(rotation.y) * cos(rotation.z) + point.y * (cos(rotation.z) * sin(rotation.x) * sin(rotation.y) - cos(rotation.x) \
                * sin(rotation.z)) + point.z * (sin(rotation.x) * sin(rotation.z) + cos(rotation.x) * cos(rotation.z) * sin(rotation.y));
                result.y = point.x * cos(rotation.y) * sin(rotation.z) + point.y * (cos(rotation.x) * cos(rotation.z) + sin(rotation.x) * sin(rotation.y) \
                * sin(rotation.z)) + point.z * (cos(rotation.x) * sin(rotation.y) * sin(rotation.z) - cos(rotation.z) * sin(rotation.x));
                result.z = -point.x * sin(rotation.y) + point.y * cos(rotation.y) * sin(rotation.x) + point.z * cos(rotation.x) * cos(rotation.y);
                return result;
            }

            template<typename T>
            Math::Vector3<T> translate(const Math::Vector3<T> &point, const Math::Vector3<T> &translation) const
            {
                return Math::Vector3<T>(point.x + translation.x, point.y + translation.y, point.z + translation.z);
            }
    };
}