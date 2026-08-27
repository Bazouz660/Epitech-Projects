/*
** EPITECH PROJECT, 2023
** B-OOP-400-STG-4-1-raytracer-basile.trebus-hamann
** File description:
** Triangle
*/

#include "Triangle.hpp"
#include "utils.hpp"

RayTracer::Triangle::Triangle(const Math::Vector3<double> a, const Math::Vector3<double> b, const Math::Vector3<double> c,
    const Math::Vector3<double> nA, const Math::Vector3<double> nB, const Math::Vector3<double> nC,
    const Color::RGB& color, const std::string &name, const Material& material)
{
    m_a = a;
    m_b = b;
    m_c = c;
    m_nA = nA;
    m_nB = nB;
    m_nC = nC;
    m_color = color;
    m_name = name;
    m_material = material;
}

RayTracer::Triangle::Triangle(const RayTracer::Triangle &other)
{
    m_a = other.m_a;
    m_b = other.m_b;
    m_c = other.m_c;
    m_nA = other.m_nA;
    m_nB = other.m_nB;
    m_nC = other.m_nC;
    m_color = other.m_color;
    m_material = other.m_material;
}

void RayTracer::Triangle::translate(const Math::Vector3<double> &translation)
{
    m_a += translation;
    m_b += translation;
    m_c += translation;
}

void RayTracer::Triangle::rotate(const Math::Vector3<double> &rotation)
{
}

void RayTracer::Triangle::scale(const Math::Vector3<double> &scale)
{
}

RayTracer::Space::AABB RayTracer::Triangle::getBounds() const
{
    Math::Vector3<double> min;
    Math::Vector3<double> max;

    min.x = std::min(m_a.x, std::min(m_b.x, m_c.x));
    min.y = std::min(m_a.y, std::min(m_b.y, m_c.y));
    min.z = std::min(m_a.z, std::min(m_b.z, m_c.z));

    max.x = std::max(m_a.x, std::max(m_b.x, m_c.x));
    max.y = std::max(m_a.y, std::max(m_b.y, m_c.y));
    max.z = std::max(m_a.z, std::max(m_b.z, m_c.z));

    return Space::AABB(min, max);
}

Math::Vector3<double> RayTracer::Triangle::getNormal() const
{
    return m_nA;
}

// checks if ray hits triangle (the coordinate system is: x goes right, y goes down, z goes away from the camera)
bool RayTracer::Triangle::hits(Ray &ray) const
{

    if (getBounds().hits(ray) == false) {
        return false;
    }
    if (ray.dir.dot(m_nA) > 0) {
        return false;
    }

    const double EPSILON = 1e-6;

    // calculate the determinant of the matrix formed by the ray direction and two edges of the triangle
    Math::Vector3<double> edge1 = m_b - m_a;
    Math::Vector3<double> edge2 = m_c - m_a;
    Math::Vector3<double> pvec = ray.dir.cross(edge2);
    double det = edge1.dot(pvec);

    // if the determinant is close to zero, the ray is parallel to the triangle plane
    if (std::fabs(det) < EPSILON) {
        return false;
    }

    // calculate the inverse of the determinant
    double inv_det = 1.0 / det;

    // calculate the vector from the ray origin to the first vertex of the triangle
    Math::Vector3<double> tvec = ray.origin - m_a;

    // calculate the u parameter of the intersection point
    double u = tvec.dot(pvec) * inv_det;

    // if u is outside the range [0, 1], the intersection point is outside the triangle
    if (u < 0.0 || u > 1.0) {
        return false;
    }

    // calculate the vector perpendicular to both the ray direction and the first edge of the triangle
    Math::Vector3<double> qvec = tvec.cross(edge1);

    // calculate the v parameter of the intersection point
    double v = ray.dir.dot(qvec) * inv_det;

    // if v is outside the range [0, 1], the intersection point is outside the triangle
    if (v < 0.0 || u + v > 1.0) {
        return false;
    }

    // calculate the distance to the intersection point
    double t = edge2.dot(qvec) * inv_det;

    // if t is negative, the intersection point is behind the ray origin
    if (t < 0.0) {
        return false;
    }

    ray.getHit().hitPosition = ray.origin + ray.dir * t;
    ray.getHit().dist = t;
    ray.getHit().normal = m_nA * (1 - u - v) + m_nB * u + m_nC * v;
    ray.getHit().obj = dynamic_cast<IPrimitive*>(const_cast<Triangle*>(this));

    // otherwise, the ray intersects the triangle
    return true;
}

