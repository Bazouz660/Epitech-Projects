/*
** EPITECH PROJECT, 2023
** B-OOP-400-STG-4-1-raytracer-basile.trebus-hamann
** File description:
** Camera
*/

#pragma once

#include "Ray.hpp"

namespace RayTracer
{
    class Camera
    {
        public:
            Camera();
            Camera(unsigned int fov, unsigned int width, unsigned int height);
            ~Camera();
            unsigned int getFov() const;
            unsigned int getWidth() const;
            unsigned int getHeight() const;

            void setFov(unsigned int);
            void setWidth(unsigned int);
            void setHeight(unsigned int);
            void setOrigin(Math::Vector3<double>);
            void setRotation(Math::Vector3<double>);

            Ray ray(double u, double v) const;

        protected:
        private:
            unsigned int m_fov;
            unsigned int m_screenResX;
            unsigned int m_screenResY;
            Math::Vector3<double> m_origin;
            Math::Vector3<double> m_rotation;
    };
}
