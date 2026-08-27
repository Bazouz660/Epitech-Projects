/*
** EPITECH PROJECT, 2023
** B-YEP-400-STG-4-1-zappy-basile.trebus-hamann
** File description:
** Chrono
*/

#pragma once

#include "common.hpp"
#include <chrono>
#include <functional>

namespace zpy {

    class Chrono {
        public:
            Chrono();
            ~Chrono();

            // starts the chrono
            void start();

            // stops the chrono
            void stop();

            // resets the chrono
            void reset();

            // returns the elapsed time in seconds
            double getElapsedTime();

            // calls the function passed as parameter if the elapsed time is greater than the time passed as parameter (in seconds)
            void timeOut(double time, std::function<void()> func);


        private:
            std::chrono::time_point<std::chrono::steady_clock> _start;
            std::chrono::time_point<std::chrono::steady_clock> _end;
            bool _isRunning;
    };

}