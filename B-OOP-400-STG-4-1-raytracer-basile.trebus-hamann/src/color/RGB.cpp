/*
** EPITECH PROJECT, 2023
** B-OOP-400-STG-4-1-raytracer-basile.trebus-hamann
** File description:
** RGB
*/

#include "Color.hpp"

namespace RayTracer::Color {

    RGB::RGB()
    {
        r = 0;
        g = 0;
        b = 0;
    }

    RGB::RGB(double r, double g, double b)
    {
        this->r = r;
        this->g = g;
        this->b = b;
    }

    RGB::RGB(const RGB &other)
    {
        r = other.r;
        g = other.g;
        b = other.b;
    }

    void RGB::clampColor()
    {
        r = std::clamp(r, 0.0, 1.0);
    }

    RGB &RGB::operator=(const RGB &other)
    {
        r = other.r;
        g = other.g;
        b = other.b;
        return *this;
    }

    RGB &RGB::operator=(RGB &&other) noexcept
    {
        r = other.r;
        g = other.g;
        b = other.b;
        return *this;
    }

    RGB RGB::operator+(const RGB &c) const
    {
        return RGB(r + c.r, g + c.g, b + c.b);
    }

    RGB RGB::operator-(const RGB &c) const
    {
        return RGB(r * c.r, g * c.g, b * c.b);
    }

    RGB RGB::operator*(const RGB &c) const
    {
        float r = c.r;
        float g = c.g;
        float b = c.b;

        return RGB(r, g, b);
    }

    RGB RGB::operator*(double t) const
    {
        float r1 = r;
        float g1 = g;
        float b1 = b;

        float r3 = r1 * t;
        float g3 = g1 * t;
        float b3 = b1 * t;

        return RGB(r3, g3, b3);
    }

    RGB RGB::operator/(double t) const
    {
        float r1 = r;
        float g1 = g;
        float b1 = b;

        float r3 = r1 / t;
        float g3 = g1 / t;
        float b3 = b1 / t;

        return RGB(r3, g3, b3);
    }

    RGB &RGB::operator+=(const RGB &c)
    {
        r += c.r;
        g += c.g;
        b += c.b;
        return *this;
    }

    RGB &RGB::operator-=(const RGB &c)
    {
        r -= c.r;
        g -= c.g;
        b -= c.b;
        return *this;
    }

    RGB &RGB::operator*=(const RGB &c)
    {
        r *= c.r;
        g *= c.g;
        b *= c.b;
        return *this;
    }

    RGB &RGB::operator*=(double t)
    {
        r *= t;
        g *= t;
        b *= t;
        return *this;
    }

    RGB &RGB::operator/=(double t)
    {
        r /= t;
        g /= t;
        b /= t;
        return *this;
    }

    bool RGB::operator==(const RGB &c) const
    {
        return r == c.r && g == c.g && b == c.b;
    }

    bool RGB::operator!=(const RGB &c) const
    {
        return r != c.r || g != c.g || b != c.b;
    }

    std::string RGB::toString() const
    {
        return std::to_string((int)std::clamp(r, 0.0, 255.0)) + " " + std::to_string((int)std::clamp(g, 0.0, 255.0)) + " " + std::to_string((int)std::clamp(b, 0.0, 255.0));
    }

    RGB& RGB::average(const RGB& other)
    {
        r = (r + other.r) / 2.0;
        g = (g + other.g) / 2.0;
        b = (b + other.b) / 2.0;
        return *this;
    }

    RGB RGB::operator+(double c) const
    {
        return RGB(r + c, g + c, b + c);
    }

    RGB RGB::operator-(double c) const
    {
        return RGB(r - c, g - c, b - c);
    }

    RGB& RGB::operator+=(double c)
    {
        r += c;
        g += c;
        b += c;
        return *this;
    }

    RGB& RGB::operator-=(double c)
    {
        r -= c;
        g -= c;
        b -= c;
        return *this;
    }

    // Applies a saturation multiplier to the color.
    void RGB::adjustSaturation(double saturationMultiplier) {
        double average = (r + g + b) / 3.0;
        r = average + saturationMultiplier * (r - average);
        g = average + saturationMultiplier * (g - average);
        b = average + saturationMultiplier * (b - average);
    }
}
