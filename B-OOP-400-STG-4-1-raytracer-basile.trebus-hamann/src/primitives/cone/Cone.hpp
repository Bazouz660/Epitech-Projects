/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** Cone
*/

#ifndef CONE_HPP_
#define CONE_HPP_

#include "APrimitive.hpp"

namespace RayTracer {

    class Cone : public APrimitive {
        public:
            Cone();
            Cone(const Cone &other);
            ~Cone() override = default;

            void translate(const Math::Vector3<double> &translation) override;
            void rotate(const Math::Vector3<double> &rotation) override;
            void scale(const Math::Vector3<double> &scale) override;

            bool hits(Ray &ray) const override;

        private:
            Math::Vector3<double> m_rotation;
    };
}

#endif /* !CONE_HPP_ */
