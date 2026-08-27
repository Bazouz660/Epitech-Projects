/*
** EPITECH PROJECT, 2023
** B-OOP-400-STG-4-1-raytracer-basile.trebus-hamann
** File description:
** Octree
*/

#pragma once

#include "common.hpp"
#include "IPrimitive.hpp"

#include <cassert>
#include <algorithm>
#include <array>
#include <memory>
#include <type_traits>
#include <vector>

namespace RayTracer::Space {

    class Octree {

        public:
            Octree(const Space::AABB &box, int threshold = 16);
            ~Octree() = default;

            void insert(const std::shared_ptr<IPrimitive> &primitive);
            void insert(const std::vector<std::shared_ptr<IPrimitive>> &primitives);

            std::vector<std::shared_ptr<IPrimitive>> query(const Space::AABB &box) const;

            void clear();

            const Space::AABB &getBox() const;

        private:
            void subdivide();
            void insert(const std::shared_ptr<IPrimitive> &primitive, const Space::AABB &box);

            Space::AABB m_box;
            int m_threshold;
            std::array<std::shared_ptr<Octree>, 8> m_children;
            std::vector<std::shared_ptr<IPrimitive>> m_primitives;
        };
    }
