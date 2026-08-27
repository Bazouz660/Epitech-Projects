/*
** EPITECH PROJECT, 2023
** B-OOP-400-STG-4-1-raytracer-basile.trebus-hamann
** File description:
** utils
*/

#pragma once

#include "common.hpp"

namespace RayTracer
{
    namespace Utils
    {
        bool equal(double a, double b);
        int randBetween(int minNum, int maxNum);
        std::vector<std::string> split(const std::string& str, const std::string& delim);
    }
}