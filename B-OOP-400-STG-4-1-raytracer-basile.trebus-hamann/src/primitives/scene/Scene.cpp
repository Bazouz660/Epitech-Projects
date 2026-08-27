/*
** EPITECH PROJECT, 2023
** B-OOP-400-STG-4-1-raytracer-basile.trebus-hamann
** File description:
** Scene
*/

#include "Scene.hpp"
#include "Plane.hpp"

namespace RayTracer {

    Scene::Scene()
    {
    }

    Scene::Scene(std::vector<sptr<IPrimitive>> primitives)
    {
        m_objects = std::move(primitives);
    }

    void Scene::translate(const Math::Vector3<double> &translation)
    {
        for (auto &primitive : m_objects)
            primitive->translate(translation);
    }

    void Scene::rotate(const Math::Vector3<double> &rotation)
    {
        for (auto &primitive : m_objects)
            primitive->rotate(rotation);
    }

    void Scene::scale(const Math::Vector3<double> &scale)
    {
        for (auto &primitive : m_objects)
            primitive->scale(scale);
    }

    bool Scene::hits(Ray &ray) const
    {
        bool hit = false;

        if (!getBounds().hits(ray))
            return false;

        double closestDist = std::numeric_limits<double>::max();

        for (auto &obj : m_objects) {
            if (obj->hits(ray) && std::abs(ray.getHit().dist) < std::abs(closestDist)) {
                closestDist = ray.getHit().dist;
                ray.getClosestHit() = ray.getHit();
                hit = true;
            }
        }
        return hit;
    }

    std::vector<sptr<IPrimitive>> Scene::getPrimitives()
    {
        std::vector<sptr<IPrimitive>> primitives;

        for (auto &obj : m_objects) {
            if (dynamic_cast<Scene *>(obj.get()) != nullptr) {
                auto scenePrimitives = dynamic_cast<Scene *>(obj.get())->getPrimitives();
                primitives.insert(primitives.end(), scenePrimitives.begin(), scenePrimitives.end());
            } else
                primitives.push_back(obj);
        }
        return primitives;
    }

    std::vector<sptr<IPrimitive>> &Scene::getObjects()
    {
        return m_objects;
    }

    void Scene::addObject(sptr<IPrimitive> obj)
    {
        m_objects.push_back(std::move(obj));
    }

    Space::AABB Scene::getBounds() const
    {
        Space::AABB bounds;

        Math::Vector3<double> min = {std::numeric_limits<double>::max(),
                                     std::numeric_limits<double>::max(),
                                     std::numeric_limits<double>::max()};
        Math::Vector3<double> max = {std::numeric_limits<double>::min(),
                                    std::numeric_limits<double>::min(),
                                    std::numeric_limits<double>::min()};

        for (auto &obj : m_objects) {
            auto primitiveBounds = obj->getBounds();
            min.x = std::min(min.x, primitiveBounds.getMin().x);
            min.y = std::min(min.y, primitiveBounds.getMin().y);
            min.z = std::min(min.z, primitiveBounds.getMin().z);
            max.x = std::max(max.x, primitiveBounds.getMax().x);
            max.y = std::max(max.y, primitiveBounds.getMax().y);
            max.z = std::max(max.z, primitiveBounds.getMax().z);
        }
        bounds.setMin(min);
        bounds.setMax(max);
        return bounds;
    }

    Space::AABB Scene::getBoundsFinite() const
    {
        Space::AABB bounds;

        Math::Vector3<double> min = {std::numeric_limits<double>::max(),
                                     std::numeric_limits<double>::max(),
                                     std::numeric_limits<double>::max()};
        Math::Vector3<double> max = {std::numeric_limits<double>::min(),
                                    std::numeric_limits<double>::min(),
                                    std::numeric_limits<double>::min()};

        for (auto &obj : m_objects) {
            if (dynamic_cast<Plane *>(obj.get()) != nullptr)
                continue;
            auto primitiveBounds = obj->getBounds();
            min.x = std::min(min.x, primitiveBounds.getMin().x);
            min.y = std::min(min.y, primitiveBounds.getMin().y);
            min.z = std::min(min.z, primitiveBounds.getMin().z);
            max.x = std::max(max.x, primitiveBounds.getMax().x);
            max.y = std::max(max.y, primitiveBounds.getMax().y);
            max.z = std::max(max.z, primitiveBounds.getMax().z);
        }
        bounds.setMin(min);
        bounds.setMax(max);
        return bounds;
    }

}