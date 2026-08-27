/*
** EPITECH PROJECT, 2023
** B-OOP-400-STG-4-1-raytracer-basile.trebus-hamann
** File description:
** Vector3
*/

#pragma once

#include "common.hpp"

namespace Math {

    template<typename T>
    class Vector3 {

        public:
            T x;
            T y;
            T z;

            Vector3(): x(0), y(0), z(0) {};
            Vector3(T x, T y, T z): x(x), y(y), z(z) {};

            Vector3(const Vector3<T> &other): x(other.x), y(other.y), z(other.z) {};
            Vector3(Vector3<T> &&other) noexcept: x(other.x), y(other.y), z(other.z) {};


            Vector3<T> &operator=(const Vector3<T> &other)
            {
                x = other.x;
                y = other.y;
                z = other.z;
                return *this;
            }

            Vector3<T> &operator=(Vector3<T> &&other) noexcept
            {
                x = other.x;
                y = other.y;
                z = other.z;
                return *this;
            }

            Vector3<T> operator+(const Vector3<T> &other) const
            {
                return Vector3(x + other.x, y + other.y, z + other.z);
            }

            Vector3<T>& operator+=(const Vector3<T> &other)
            {
                x += other.x;
                y += other.y;
                z += other.z;
                return *this;
            }

            Vector3<T> operator-(const Vector3<T> &other) const
            {
                return Vector3(x - other.x, y - other.y, z - other.z);
            }

            Vector3<T> operator-=(const Vector3<T> &other) const
            {
                return Vector3(x -= other.x, y -= other.y, z -= other.z);
            }

            Vector3<T> operator*(const Vector3<T> &other) const
            {
                return Vector3(x * other.x, y * other.y, z * other.z);
            }

            Vector3<T> operator*=(const Vector3<T> &other) const
            {
                return Vector3(x *= other.x, y *= other.y, z *= other.z);
            }

            Vector3<T> operator/(const Vector3<T> &other) const
            {
                return Vector3(x / other.x, y / other.y, z / other.z);
            }

            Vector3<T> operator/=(const Vector3<T> &other) const
            {
                return Vector3(x /= other.x, y /= other.y, z /= other.z);
            }

            Vector3<T> operator+(T other) const
            {
                return Vector3(x + other, y + other, z + other);
            }

            Vector3<T> operator+=(T other) const
            {
                return Vector3(x += other, y += other, z += other);
            }

            Vector3<T> operator-(T other) const
            {
                return Vector3(x - other, y - other, z - other);
            }

            Vector3<T> operator-=(T other) const
            {
                return Vector3(x -= other, y -= other, z -= other);
            }

            Vector3<T> operator*(const T& scalar) const
            {
                return Vector3<T>(x * scalar, y * scalar, z * scalar);
            }

            Vector3<T> operator*=(T other) const
            {
                return Vector3(x *= other, y *= other, z *= other);
            }

            Vector3<T> operator/(T other) const
            {
                return Vector3(x / other, y / other, z / other);
            }

            Vector3<T> operator/=(T other) const
            {
                return Vector3(x /= other, y /= other, z /= other);
            }

            bool operator==(const Vector3<T> &other) const
            {
                return x == other.x && y == other.y && z == other.z;
            }

            bool operator!=(const Vector3<T> &other) const
            {
                return x != other.x || y != other.y || z != other.z;
            }

            bool operator<(const Vector3<T> &other) const
            {
                return x < other.x && y < other.y && z < other.z;
            }

            bool operator<=(const Vector3<T> &other) const
            {
                return x <= other.x && y <= other.y && z <= other.z;
            }

            bool operator>(const Vector3<T> &other) const
            {
                return x > other.x && y > other.y && z > other.z;
            }

            bool operator>=(const Vector3<T> &other) const
            {
                return x >= other.x && y >= other.y && z >= other.z;
            }

            T length() const
            {
                return sqrt(x * x + y * y + z * z);
            }

            T lengthSquared() const
            {
                return x * x + y * y + z * z;
            }

            T distance(const Vector3<T> &other) const
            {
                return (*this - other).length();
            }

            Vector3<T> normalize() const
            {
                T len = length();
                return Vector3(x / len, y / len, z / len);
            }

            T dot(const Vector3<T> &other) const
            {
                return x * other.x + y * other.y + z * other.z;
            }

            Vector3<T> rotate(const Vector3<T> &rot) const
            {
                T cosX = cos(rot.x);
                T sinX = sin(rot.x);
                T cosY = cos(rot.y);
                T sinY = sin(rot.y);
                T cosZ = cos(rot.z);
                T sinZ = sin(rot.z);

                T x = this->x;
                T y = this->y;
                T z = this->z;

                // rotation around x
                T xy = cosX * y - sinX * z;
                T xz = sinX * y + cosX * z;

                // rotation around y
                T yz = cosY * xz - sinY * x;
                T yx = sinY * xz + cosY * x;

                // rotation around z
                T zx = cosZ * yx - sinZ * xy;
                T zy = sinZ * yx + cosZ * xy;

                return Vector3(zx, zy, yz);
            }

            Vector3<T> cross(const Vector3<T> &other) const
            {
                return Vector3(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
            }

            Vector3<T> invert() const
            {
                return Vector3(-x, -y, -z);
            }

            ~Vector3() = default;
    };

    template<typename T>
    Vector3<T> operator*(const T& scalar, const Vector3<T>& vector) {
        return vector * scalar;
    }

    template<typename T>
    Vector3<T> operator/(const T& scalar, const Vector3<T>& vector) {
        return vector / scalar;
    }

    template<typename T>
    std::ostream& operator<<(std::ostream& os, const Vector3<T>& vector) {
        os << "(" << vector.x << ", " << vector.y << ", " << vector.z << ")";
        return os;
    }
}

