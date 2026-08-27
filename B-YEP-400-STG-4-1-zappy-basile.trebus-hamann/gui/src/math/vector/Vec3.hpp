/*
** EPITECH PROJECT, 2023
** Raylib_test
** File description:
** Vector3
*/

#pragma once

#include "common.hpp"

namespace zpy {

    class Vec3 : public ::Vector3 {
        public:
            Vec3() = default;
            Vec3(const ::Vector3 &other) : ::Vector3{other.x, other.y, other.z} {};
            Vec3(const Vec3& other) : ::Vector3{other.x, other.y, other.z} {};
            Vec3(const float &x, const float &y, const float &z) : ::Vector3{x, y, z} {};
            ~Vec3() = default;

            Vec3 operator+(const Vec3 &other) const { return {x + other.x, y + other.y, z + other.z}; }
            Vec3 operator-(const Vec3 &other) const { return {x - other.x, y - other.y, z - other.z}; }
            Vec3 operator*(const Vec3 &other) const { return Vec3{x * other.x, y * other.y, z * other.z}; }
            Vec3 operator/(const Vec3 &other) const { return Vec3{x / other.x, y / other.y, z / other.z}; }

            Vec3 operator+(const float &other) const { return Vec3{x + other, y + other, z + other}; }
            Vec3 operator-(const float &other) const { return Vec3{x - other, y - other, z - other}; }
            Vec3 operator*(const float &other) const { return Vec3{x * other, y * other, z * other}; }
            Vec3 operator/(const float &other) const { return Vec3{x / other, y / other, z / other}; }

            Vec3 operator+=(const Vec3 &other) { return Vec3{x += other.x, y += other.y, z += other.z}; }
            Vec3 operator-=(const Vec3 &other) { return Vec3{x -= other.x, y -= other.y, z -= other.z}; }
            Vec3 operator*=(const Vec3 &other) { return Vec3{x *= other.x, y *= other.y, z *= other.z}; }
            Vec3 operator/=(const Vec3 &other) { return Vec3{x /= other.x, y /= other.y, z /= other.z}; }

            Vec3 operator+=(const float &other) { return Vec3{x += other, y += other, z += other}; }
            Vec3 operator-=(const float &other) { return Vec3{x -= other, y -= other, z -= other}; }
            Vec3 operator*=(const float &other) { return Vec3{x *= other, y *= other, z *= other}; }
            Vec3 operator/=(const float &other) { return Vec3{x /= other, y /= other, z /= other}; }

            bool operator==(const Vec3 &other) const { return x == other.x && y == other.y && z == other.z; }
            bool operator!=(const Vec3 &other) const { return x != other.x || y != other.y || z != other.z; }

            Vec3 operator=(const Vec3 &other) { return Vec3{x = other.x, y = other.y, z = other.z}; }

            Vec3 operator=(const float &other) { return Vec3{x = other, y = other, z = other}; }

            Vec3 operator-() const { return Vec3{-x, -y, -z}; }

            float length() const { return std::sqrt(x * x + y * y + z * z); }
            float distance(const Vec3 &other) const { return std::sqrt(std::pow(x - other.x, 2) + std::pow(y - other.y, 2) + std::pow(z - other.z, 2)); }
            float dot(const Vec3 &other) const { return x * other.x + y * other.y + z * other.z; }
            float angle(const Vec3 &other) const { return std::acos(dot(other) / (length() * other.length())); }
            Vec3 cross(const Vec3 &other) const { return Vec3{y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x}; }
            Vec3 normalize() const { return Vec3{x / length(), y / length(), z / length()}; }
    };

}