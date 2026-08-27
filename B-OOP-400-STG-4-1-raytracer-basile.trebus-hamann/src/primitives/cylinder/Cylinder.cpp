/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Cylinder
*/

#include "Cylinder.hpp"

namespace RayTracer {

    Cylinder::Cylinder(const Math::Vector3<double> &center,  const Math::Vector3<double> &axis,
    double height, double radius, const Color::RGB& color , const std::string &name, const Material& material)
    {
        m_center = center;
        m_axis = axis;
        m_height = height;
        m_radius = radius;
        m_material = material;
        m_color = color;
        m_name = name;
    }

    Cylinder::Cylinder(const Cylinder &other)
    {
        m_center = other.m_center;
        m_axis = other.m_axis;
        m_height = other.m_height;
        m_material = other.m_material;
        m_radius = other.m_radius;
        m_color = other.m_color;
    }

    // checks if the ray hits the cylinder (the cylinder is infinite)
    bool Cylinder::hits(Ray &ray) const
    {
        Math::Vector3<double> oc = ray.origin - m_center;
        double a = ray.dir.dot(ray.dir) - m_axis.dot(ray.dir) * m_axis.dot(ray.dir);
        double b = 2.0 * (oc.dot(ray.dir) - m_axis.dot(oc) * m_axis.dot(ray.dir));
        double c = oc.dot(oc) - m_axis.dot(oc) * m_axis.dot(oc) - m_radius * m_radius;
        double discriminant = b * b - 4 * a * c;
        if (discriminant < 0)
            return false;
        double t1 = (-b - sqrt(discriminant)) / (2.0 * a);
        double t2 = (-b + sqrt(discriminant)) / (2.0 * a);
        if (t1 < 0 && t2 < 0)
            return false;
        return true;
    }

    void Cylinder::translate(const Math::Vector3<double> &translation)
    {

    }

    void Cylinder::rotate(const Math::Vector3<double> &rotation)
    {

    }

    void Cylinder::scale(const Math::Vector3<double> &scale)
    {

    }

    Space::AABB Cylinder::getBounds() const
    {
        Math::Vector3<double> min = m_center - m_axis * m_height / 2.0;
        Math::Vector3<double> max = m_center + m_axis * m_height / 2.0;
        return Space::AABB(min, max);
    }
}