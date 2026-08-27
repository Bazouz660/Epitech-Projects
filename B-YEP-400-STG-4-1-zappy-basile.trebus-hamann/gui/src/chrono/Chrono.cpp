/*
** EPITECH PROJECT, 2023
** B-CCP-400-STG-4-1-theplazza-marie.giacomel
** File description:
** Chrono
*/

#include "Chrono.hpp"

namespace zpy {

    Chrono::Chrono()
    {
        _isRunning = false;
    }

    Chrono::~Chrono()
    {
    }

    void Chrono::start()
    {
        _start = std::chrono::steady_clock::now();
        _isRunning = true;
    }

    void Chrono::stop()
    {
        _end = std::chrono::steady_clock::now();
        _isRunning = false;
    }

    void Chrono::reset()
    {
        _start = std::chrono::steady_clock::now();
        _end = std::chrono::steady_clock::now();
    }

    double Chrono::getElapsedTime()
    {
        if (_isRunning)
            _end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = _end - _start;
        return elapsed_seconds.count();
    }

    void Chrono::timeOut(double time, std::function<void()> func)
    {
        if (getElapsedTime() >= time) {
            func();
            reset();
        }
    }

}