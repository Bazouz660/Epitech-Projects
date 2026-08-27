/*
** EPITECH PROJECT, 2023
** B-OOP-400-STG-4-1-raytracer-basile.trebus-hamann
** File description:
** AABB
*/

#include "AABB.hpp"

namespace RayTracer::Space {

    AABB::AABB()
    : m_min(Math::Vector3<double>(0, 0, 0)), m_max(Math::Vector3<double>(0, 0, 0))
    {
    }

    AABB::AABB(const Math::Vector3<double> &min, const Math::Vector3<double> &max)
    : m_min(min), m_max(max)
    {
    }

    bool AABB::hits(Ray &ray) const
    {
        Math::Vector3<double> inv_dir(1.0 / ray.dir.x, 1.0 / ray.dir.y, 1.0 / ray.dir.z);

        double tx1 = (m_min.x - ray.origin.x) * inv_dir.x;
        double tx2 = (m_max.x - ray.origin.x) * inv_dir.x;
        double ty1 = (m_min.y - ray.origin.y) * inv_dir.y;
        double ty2 = (m_max.y - ray.origin.y) * inv_dir.y;

        double tmin = std::max(std::min(tx1, tx2), std::min(ty1, ty2));
        double tmax = std::min(std::max(tx1, tx2), std::max(ty1, ty2));

        if (ray.dir.z == 0.0)
            return (tmax >= tmin) && (tmin <= (m_max.z - ray.origin.z) * inv_dir.z);

        double tz1 = (m_min.z - ray.origin.z) * inv_dir.z;
        double tz2 = (m_max.z - ray.origin.z) * inv_dir.z;

        tmin = std::max(tmin, std::min(tz1, tz2));
        tmax = std::min(tmax, std::max(tz1, tz2));

        return tmax >= tmin;
    }

    bool AABB::contains(const Math::Vector3<double> &point) const
    {
        return (point.x > m_min.x && point.x < m_max.x &&
            point.y > m_min.y && point.y < m_max.y &&
            point.z > m_min.z && point.z < m_max.z);
    }

    bool AABB::contains(const AABB &other) const
    {
        return (
            m_min.x <= other.getMin().x &&
            m_max.x >= other.getMax().x &&
            m_min.y <= other.getMin().y &&
            m_max.y >= other.getMax().y &&
            m_min.z <= other.getMin().z &&
            m_max.z >= other.getMax().z
        );
    }

    bool AABB::intersects(const AABB &other) const
    {
        return (
            m_min.x <= other.getMax().x &&
            m_max.x >= other.getMin().x &&
            m_min.y <= other.getMax().y &&
            m_max.y >= other.getMin().y &&
            m_min.z <= other.getMax().z &&
            m_max.z >= other.getMin().z
        );
    }

    const Math::Vector3<double> &AABB::getMin() const
    {
        return m_min;
    }

    const Math::Vector3<double> &AABB::getMax() const
    {
        return m_max;
    }

    const Math::Vector3<double> AABB::getCenter() const
    {
        return Math::Vector3<double>(
            (m_min.x + m_max.x) / 2,
            (m_min.y + m_max.y) / 2,
            (m_min.z + m_max.z) / 2
        );
    }

    void AABB::setMin(const Math::Vector3<double> &min)
    {
        m_min = min;
    }

    void AABB::setMax(const Math::Vector3<double> &max)
    {
        m_max = max;
    }

}