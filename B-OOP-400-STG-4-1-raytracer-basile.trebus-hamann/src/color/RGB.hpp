/*
** EPITECH PROJECT, 2023
** B-OOP-400-STG-4-1-raytracer-basile.trebus-hamann
** File description:
** RGB
*/

#pragma once

#include "common.hpp"

namespace RayTracer::Color
{
    class RGB
    {
        public:
            RGB();
            RGB(double r, double g, double b);
            RGB(const RGB &other);
            ~RGB() = default;

            double r;
            double g;
            double b;

            RGB& average(const RGB &other);

            RGB &operator=(const RGB &other);
            RGB &operator=(RGB &&other) noexcept;

            RGB operator+(const RGB &c) const;
            RGB operator-(const RGB &c) const;
            RGB operator*(const RGB &c) const;
            RGB operator*(double t) const;
            RGB operator/(double t) const;
            RGB operator+(double t) const;
            RGB operator-(double t) const;

            RGB &operator+=(const RGB &c);
            RGB &operator-=(const RGB &c);
            RGB &operator*=(const RGB &c);
            RGB &operator*=(double t);
            RGB &operator/=(double t);
            RGB &operator+=(double t);
            RGB &operator-=(double t);

            bool operator==(const RGB &c) const;
            bool operator!=(const RGB &c) const;

            void adjustSaturation(double saturationMultiplier);

            std::string toString() const;


        private:
            void clampColor();
    };
}
