/*
** EPITECH PROJECT, 2023
** B-OOP-400-STG-4-1-raytracer-basile.trebus-hamann
** File description:
** ALight
*/

#pragma once

#include "ILight.hpp"

namespace RayTracer {

    class ALight : public ILight {

        public:
            ALight(const Math::Vector3<double> &position, const Color::RGB &color, double intensity)
            {
                m_position = position;
                m_color = color;
                m_intensity = intensity;
            }

            virtual ~ALight() override = default;

            virtual void setIntensity(double intensity) override { m_intensity = intensity; }
            virtual void setColor(const Color::RGB &color) override { m_color = color;}
            virtual void setPosition(const Math::Vector3<double> &position) override { m_position = position; }

            virtual double getIntensity() const override { return m_intensity; }
            virtual const Color::RGB& getColor() const override { return m_color; }
            virtual Math::Vector3<double> getPosition() const override { return m_position; }

        protected:
            Math::Vector3<double> m_position;
            Color::RGB m_color;
            double m_intensity;
    };

}