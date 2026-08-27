/*
** EPITECH PROJECT, 2023
** B-OOP-400-STG-4-1-raytracer-basile.trebus-hamann
** File description:
** Scene
*/

#pragma once

#include "APrimitive.hpp"

namespace RayTracer {

    class Scene : public APrimitive {
        public:
            Scene();
            Scene(std::vector<sptr<IPrimitive>> primitives);
            virtual ~Scene() override = default;

            std::vector<sptr<IPrimitive>> &getObjects();
            std::vector<sptr<IPrimitive>> getPrimitives();

            void addObject(sptr<IPrimitive> primitive);

            void translate(const Math::Vector3<double> &translation) override;
            void rotate(const Math::Vector3<double> &rotation) override;
            void scale(const Math::Vector3<double> &scale) override;

            Space::AABB getBounds() const override;
            Space::AABB getBoundsFinite() const;

            bool hits(Ray &ray) const override;

        private:
            std::vector<sptr<IPrimitive>> m_objects;


    };

}