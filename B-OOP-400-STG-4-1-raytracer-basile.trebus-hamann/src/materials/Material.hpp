/*
** EPITECH PROJECT, 2023
** B-OOP-400-STG-4-1-raytracer-basile.trebus-hamann
** File description:
** AMaterial
*/

#pragma once

#include "common.hpp"

namespace RayTracer {

    class Material {
        public:
            Material(double shininess = 0, double reflectivity = 0,
            double transparency = 0, double refractiveIndex = 0)
            {
                m_reflectivity = reflectivity;
                m_refractiveIndex = refractiveIndex;
                m_shininess = shininess;
                m_transparency = transparency;
            }

            ~Material() = default;

            void setShininess(double shininess) { m_shininess = shininess;}
            double getShininess() const { return m_shininess; }

            void setReflectivity(double reflectivity) { m_reflectivity = reflectivity;}
            double getReflectivity() const { return m_reflectivity;}

            void setTransparency(double transparency) { m_transparency = transparency;}
            double getTransparency() const { return m_transparency;}

            void setRefractiveIndex(double refractiveIndex) { m_refractiveIndex = refractiveIndex;}
            double getRefractiveIndex() const { return m_refractiveIndex;}

        private:
            double m_shininess;
            double m_reflectivity;
            double m_transparency;
            double m_refractiveIndex;
    };
}