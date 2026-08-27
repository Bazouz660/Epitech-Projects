/*
** EPITECH PROJECT, 2023
** Raylib_test
** File description:
** Vector4
*/

#pragma once

#include "common.hpp"

namespace zpy {

    class Vec4 : public ::Vector4 {
        public:
            Vec4() = default;
            Vec4(const ::Vector4 &other) : ::Vector4{other.x, other.y, other.z, other.w} {};
            Vec4(const Vec4& other) : ::Vector4{other.x, other.y, other.z, other.w} {};
            Vec4(const float &x, const float &y, const float &z, const float &w) : ::Vector4{x, y, z, w} {};
            ~Vec4() = default;

            Vec4 operator+(const Vec4 &other) const { return {x + other.x, y + other.y, z + other.z, w + other.w}; }
            Vec4 operator-(const Vec4 &other) const { return {x - other.x, y - other.y, z - other.z, w - other.w}; }
            Vec4 operator*(const Vec4 &other) const { return Vec4{x * other.x, y * other.y, z * other.z, w * other.w}; }
            Vec4 operator/(const Vec4 &other) const { return Vec4{x / other.x, y / other.y, z / other.z, w / other.w}; }

            Vec4 operator+(const float &other) const { return Vec4{x + other, y + other, z + other, w + other}; }
            Vec4 operator-(const float &other) const { return Vec4{x - other, y - other, z - other, w - other}; }
            Vec4 operator*(const float &other) const { return Vec4{x * other, y * other, z * other, w * other}; }
            Vec4 operator/(const float &other) const { return Vec4{x / other, y / other, z / other, w / other}; }

            Vec4 operator+=(const Vec4 &other) { return Vec4{x += other.x, y += other.y, z += other.z, w += other.w}; }
            Vec4 operator-=(const Vec4 &other) { return Vec4{x -= other.x, y -= other.y, z -= other.z, w -= other.w}; }
            Vec4 operator*=(const Vec4 &other) { return Vec4{x *= other.x, y *= other.y, z *= other.z, w *= other.w}; }
            Vec4 operator/=(const Vec4 &other) { return Vec4{x /= other.x, y /= other.y, z /= other.z, w /= other.w}; }

            Vec4 operator+=(const float &other) { return Vec4{x += other, y += other, z += other, w += other}; }
            Vec4 operator-=(const float &other) { return Vec4{x -= other, y -= other, z -= other, w -= other}; }
            Vec4 operator*=(const float &other) { return Vec4{x *= other, y *= other, z *= other, w *= other}; }
            Vec4 operator/=(const float &other) { return Vec4{x /= other, y /= other, z /= other, w /= other}; }

            bool operator==(const Vec4 &other) const { return x == other.x && y == other.y && z == other.z && w == other.w; }
            bool operator!=(const Vec4 &other) const { return x != other.x || y != other.y || z != other.z || w != other.w; }

            Vec4 operator=(const Vec4 &other) { return Vec4{x = other.x, y = other.y, z = other.z, w = other.w}; }

            Vec4 operator=(const float &other) { return Vec4{x = other, y = other, z = other, w = other}; }

            Vec4 operator-() const { return Vec4{-x, -y, -z, -w}; }

            float length() const { return std::sqrt(x * x + y * y + z * z + w * w); }
            float distance(const Vec4 &other) const { return std::sqrt(std::pow(x - other.x, 2) + std::pow(y - other.y, 2) + std::pow(z - other.z, 2) + std::pow(w - other.w, 2)); }
            float dot(const Vec4 &other) const { return x * other.x + y * other.y + z * other.z + w * other.w; }
            float angle(const Vec4 &other) const { return std::acos(dot(other) / (length() * other.length())); }
            Vec4 cross(const Vec4 &other) const { return Vec4{y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x, 0}; }
            Vec4 normalize() const { return *this / length(); }
    };

}