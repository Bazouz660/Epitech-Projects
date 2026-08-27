/*
** EPITECH PROJECT, 2023
** B-OOP-400-STG-4-1-raytracer-basile.trebus-hamann
** File description:
** Plane
*/

#include "Plane.hpp"

namespace RayTracer {

    Plane::Plane(const Math::Vector3<double> &normal, const Math::Vector3<double> &rdPoint,
    const Color::RGB &color, const std::string &name, const Material &material)
    {
        m_normal = normal;
        m_rdPoint = rdPoint;
        m_name = name;
        m_color = color;
        m_material = material;
    }

    Plane::Plane(const Plane &other)
    {
        m_normal = other.m_normal;
        m_rdPoint = other.m_rdPoint;
        m_color = other.getColor();
        m_material = other.getMaterial();
    }


    bool Plane::hits(Ray &ray) const
    {
        double t = (m_normal.dot(m_rdPoint - ray.origin)) / (m_normal.dot(ray.dir));

        if (t < 0 || m_normal.dot(ray.dir) == 0)
            return (false);
        Math::Vector3<double> intersection_point = ray.origin + t * ray.dir;
        ray.getHit().dist = t;
        ray.getHit().obj = (IPrimitive *)this;
        ray.getHit().hitPosition = intersection_point;
        ray.getHit().normal = m_normal;
        return (true);
    }

    Plane &Plane::operator=(const Plane &other)
    {
        m_normal = other.m_normal;
        m_rdPoint = other.m_rdPoint;
        m_material = other.getMaterial();
        return *this;
    }

    Plane &Plane::operator=(Plane &&other) noexcept
    {
        m_normal = other.m_normal;
        m_rdPoint = other.m_rdPoint;
        m_material = other.getMaterial();
        return *this;
    }

    void Plane::translate(const Math::Vector3<double> &translation)
    {
        m_rdPoint += translation;
    }

    void Plane::rotate(const Math::Vector3<double> &rotation)
    {
    }

    void Plane::scale(const Math::Vector3<double> &scale)
    {
        m_rdPoint = scale;
    }

    Space::AABB Plane::getBounds() const
    {
        Math::Vector3<double> min = Math::Vector3<double>(-INFINITY, -INFINITY, -INFINITY);
        Math::Vector3<double> max = Math::Vector3<double>(INFINITY, INFINITY, INFINITY);
        return Space::AABB(min, max);
    }

}