/*
** EPITECH PROJECT, 2023
** B-OOP-400-STG-4-1-raytracer-basile.trebus-hamann
** File description:
** Ray
*/

#include "Ray.hpp"

namespace RayTracer {

    Ray::Ray()
    {
        origin = Math::Vector3<double>(0, 0, 0);
        dir = Math::Vector3<double>(0, 0, 0);
        m_finalColor = Color::RGB(0, 0, 0);
    }

    Ray::Ray(const Math::Vector3<double> &origin, const Math::Vector3<double> &direction)
    {
        this->origin = origin;
        dir = direction.normalize();
        m_finalColor = Color::RGB(0, 0, 0);
    }

    Ray::Ray(const Ray &other)
    {
        origin = other.origin;
        dir = other.dir;
    }

    Ray::Ray(Ray &&other) noexcept
    {
        origin = other.origin;
        dir = other.dir;
    }

    Ray &Ray::operator=(const Ray &other)
    {
        origin = other.origin;
        dir = other.dir;
        return *this;
    }

    Ray &Ray::operator=(Ray &&other) noexcept
    {
        origin = other.origin;
        dir = other.dir;
        return *this;
    }

    Ray::hit_t &Ray::getHit()
    {
        return m_hit;
    }

    Ray::hit_t &Ray::getClosestHit()
    {
        return m_closestHit;
    }

}