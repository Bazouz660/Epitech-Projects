/*
** EPITECH PROJECT, 2023
** Raylib_test
** File description:
** Vector2
*/

#pragma once

#include "common.hpp"

namespace zpy {

    class Vec2 : public ::Vector2 {
        public:
            Vec2() = default;
            Vec2(const ::Vector2 &other) : ::Vector2{other.x, other.y} {};
            Vec2(const Vec2& other) : ::Vector2{other.x, other.y} {};
            Vec2(const float &x, const float &y) : ::Vector2{x, y} {};
            ~Vec2() = default;

            Vec2 operator+(const Vec2 &other) const { return Vec2{x + other.x, y + other.y}; }
            Vec2 operator-(const Vec2 &other) const { return Vec2{x - other.x, y - other.y}; }
            Vec2 operator*(const Vec2 &other) const { return Vec2{x * other.x, y * other.y}; }
            Vec2 operator/(const Vec2 &other) const { return Vec2{x / other.x, y / other.y}; }

            Vec2 operator+(const float &other) const { return Vec2{x + other, y + other}; }
            Vec2 operator-(const float &other) const { return Vec2{x - other, y - other}; }
            Vec2 operator*(const float &other) const { return Vec2{x * other, y * other}; }
            Vec2 operator/(const float &other) const { return Vec2{x / other, y / other}; }

            Vec2 operator+=(const Vec2 &other) { return Vec2{x += other.x, y += other.y}; }
            Vec2 operator-=(const Vec2 &other) { return Vec2{x -= other.x, y -= other.y}; }
            Vec2 operator*=(const Vec2 &other) { return Vec2{x *= other.x, y *= other.y}; }
            Vec2 operator/=(const Vec2 &other) { return Vec2{x /= other.x, y /= other.y}; }

            Vec2 operator+=(const float &other) { return Vec2{x += other, y += other}; }
            Vec2 operator-=(const float &other) { return Vec2{x -= other, y -= other}; }
            Vec2 operator*=(const float &other) { return Vec2{x *= other, y *= other}; }
            Vec2 operator/=(const float &other) { return Vec2{x /= other, y /= other}; }

            bool operator==(const Vec2 &other) const { return x == other.x && y == other.y; }
            bool operator!=(const Vec2 &other) const { return x != other.x || y != other.y; }

            Vec2 operator=(const Vec2 &other) { return Vec2{x = other.x, y = other.y}; }

            Vec2 operator=(const float &other) { return Vec2{x = other, y = other}; }

            Vec2 operator-() const { return Vec2{-x, -y}; }

            float length() const { return sqrtf(x * x + y * y); }
            float distance(const Vec2 &other) const { return sqrtf(powf(x - other.x, 2) + powf(y - other.y, 2)); }
            float dot(const Vec2 &other) const { return x * other.x + y * other.y; }
            float angle(const Vec2 &other) const { return acosf(dot(other) / (length() * other.length())); }
            float cross(const Vec2 &other) const { return x * other.y - y * other.x; }
            Vec2 normalize() const { return Vec2{x / length(), y / length()}; }
    };
}