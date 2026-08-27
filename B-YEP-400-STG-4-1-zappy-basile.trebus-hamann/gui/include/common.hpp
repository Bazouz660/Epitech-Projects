/*
** EPITECH PROJECT, 2023
** B-YEP-400-STG-4-1-zappy-basile.trebus-hamann
** File description:
** common
*/

#include <string>
#include <iostream>
#include <memory>
#include <cmath>
#include <unordered_map>
#include <map>
#include <vector>
#include <algorithm>
#include <functional>
#include <memory>
#include "raylib.h"
#include "raymath.h"

#if defined(PLATFORM_DESKTOP)
    #define GLSL_VERSION            330
#else   // PLATFORM_RPI, PLATFORM_ANDROID, PLATFORM_WEB
    #define GLSL_VERSION            100
#endif

#define RAD (180 / PI)

#define DEG_TO_RAD(angle) ((angle) * PI / 180.0)
#define RAD_TO_DEG(angle) ((angle) * 180.0 / PI)

#define uptr std::unique_ptr
#define sptr std::shared_ptr
#define wptr std::weak_ptr
