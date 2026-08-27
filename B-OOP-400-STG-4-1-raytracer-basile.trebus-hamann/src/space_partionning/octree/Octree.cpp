/*
** EPITECH PROJECT, 2023
** B-OOP-400-STG-4-1-raytracer-basile.trebus-hamann
** File description:
** Octree
*/

#include "Octree.hpp"

namespace RayTracer::Space {

    Octree::Octree(const Space::AABB &box, int threshold)
        : m_box(box), m_threshold(threshold), m_children{}, m_primitives{}
    {
        // Initialize children to nullptr
        std::fill_n(m_children.begin(), 8, nullptr);
    }

    void Octree::insert(const std::shared_ptr<IPrimitive> &primitive)
    {
        insert(primitive, m_box);
    }

    void Octree::insert(const std::vector<std::shared_ptr<IPrimitive>> &primitives)
    {
        for (const auto &primitive : primitives)
            insert(primitive);
    }

    void Octree::insert(const std::shared_ptr<IPrimitive> &primitive, const Space::AABB &box)
    {
        if (!m_box.intersects(box))
            return;
        if (m_children[0] != nullptr) {
            // Only insert into child that fully contains the primitive
            for (const auto &child : m_children) {
                if (child->getBox().contains(primitive->getBounds()))
                    child->insert(primitive, primitive->getBounds());
            }
            return;
        }
        m_primitives.push_back(primitive);
        if (m_primitives.size() > m_threshold)
            subdivide();
    }

void Octree::subdivide()
{
    auto min = m_box.getMin();
    auto max = m_box.getMax();
    auto center = m_box.getCenter();
    m_children[0] = std::make_shared<Octree>(Space::AABB(min, center), m_threshold);
    m_children[1] = std::make_shared<Octree>(Space::AABB(Math::Vector3<double>(center.x, min.y, min.z), Math::Vector3<double>(max.x, center.y, center.z)), m_threshold);
    m_children[2] = std::make_shared<Octree>(Space::AABB(Math::Vector3<double>(center.x, min.y, center.z), Math::Vector3<double>(max.x, center.y, max.z)), m_threshold);
    m_children[3] = std::make_shared<Octree>(Space::AABB(Math::Vector3<double>(min.x, min.y, center.z), Math::Vector3<double>(center.x, center.y, max.z)), m_threshold);
    m_children[4] = std::make_shared<Octree>(Space::AABB(Math::Vector3<double>(min.x, center.y, min.z), Math::Vector3<double>(center.x, max.y, center.z)), m_threshold);
    m_children[5] = std::make_shared<Octree>(Space::AABB(Math::Vector3<double>(center.x, center.y, min.z), Math::Vector3<double>(max.x, max.y, center.z)), m_threshold);
    m_children[6] = std::make_shared<Octree>(Space::AABB(Math::Vector3<double>(center.x, center.y, center.z), Math::Vector3<double>(max)), m_threshold);
    m_children[7] = std::make_shared<Octree>(Space::AABB(Math::Vector3<double>(min.x, center.y, center.z), Math::Vector3<double>(center.x, max.y, max.z)), m_threshold);
    for (const auto &primitive : m_primitives) {
        for (const auto &child : m_children) {
            child->insert(primitive, primitive->getBounds());
        }
    }
    m_primitives.clear();
}


std::vector<std::shared_ptr<IPrimitive>> Octree::query(const Space::AABB &box) const
{
    std::vector<std::shared_ptr<IPrimitive>> primitives;
    if (!m_box.intersects(box))
        return primitives;
    if (m_children[0] != nullptr) {
        // Check which children intersect with the query box
        for (const auto &child : m_children) {
            if (child->getBox().intersects(box)) {
                auto childPrimitives = child->query(box);
                primitives.insert(primitives.end(), childPrimitives.begin(), childPrimitives.end());
            }
        }
        return primitives;
    }
    // Only check primitives that intersect with the query box
    for (const auto &primitive : m_primitives) {
        if (box.intersects(primitive->getBounds()))
            primitives.push_back(std::move(primitive));
    }
    return primitives;
}


    const Space::AABB &Octree::getBox() const
    {
        return m_box;
    }

    void Octree::clear()
    {
        for (const auto &child : m_children)
            child->clear();
        m_primitives.clear();
    }

}