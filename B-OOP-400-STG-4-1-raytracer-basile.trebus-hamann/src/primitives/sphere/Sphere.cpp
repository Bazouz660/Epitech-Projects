/*
** EPITECH PROJECT, 2023
** B-OOP-400-STG-4-1-raytracer-basile.trebus-hamann
** File description:
** Sphere
*/

#include "Sphere.hpp"

namespace RayTracer
{
    Sphere::Sphere(const Math::Vector3<double> &center, double radius,
    const Color::RGB &color, const std::string &name, const Material &material)
    {
        m_center = center;
        m_radius = radius;
        m_name = name;
        m_color = color;
        m_material = material;
    }

    Sphere::Sphere(const Sphere &other)
    {
        m_center = other.m_center;
        m_radius = other.m_radius;
        m_material = other.getMaterial();
    }

    bool Sphere::hits(Ray &ray) const
    {
        Math::Vector3<double> oc = ray.origin - m_center;

        if (!getBounds().hits(ray))
            return false;

        double a = ray.dir.dot(ray.dir);
        double b = 2.0 * oc.dot(ray.dir);
        double c = oc.dot(oc) - m_radius * m_radius;
        double discriminant = b * b - 4.0 * a * c;

        if (discriminant < 0)
            return false;
        ray.getHit().dist = (-b - std::sqrt(discriminant)) / (2.0 * a);
        if (ray.getHit().dist < 0)
            return false;
        ray.getHit().obj = (IPrimitive *)this;
        ray.getHit().hitPosition = ray.origin + ray.dir * ray.getHit().dist;
        ray.getHit().normal = ray.getHit().hitPosition - m_center;
        return true;
    }

    void Sphere::translate(const Math::Vector3<double> &translation)
    {
        m_center += translation;
    }

    void Sphere::rotate(const Math::Vector3<double> &rotation)
    {
        m_rotation = rotation;
    }

    void Sphere::scale(const Math::Vector3<double> &scale)
    {
        m_center = scale;
        m_radius = scale.x;
    }

    double Sphere::getRadius() const
    {
        return m_radius;
    }

    Math::Vector3<double> Sphere::getCenter() const
    {
        return m_center;
    }

    Space::AABB Sphere::getBounds() const
    {
        return Space::AABB(m_center - m_radius, m_center + m_radius);
    }

}