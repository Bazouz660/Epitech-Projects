/*
** EPITECH PROJECT, 2023
** B-CPP-500-STG-5-2-rtype-julian.lambert
** File description:
** console
*/

#ifndef EXNG_CONSOLE_HPP
#define EXNG_CONSOLE_HPP

namespace exng::console {

    // Make the attached terminal understand the ANSI escape sequences used by
    // the logger. This is a no-op on Linux, and enables the virtual terminal
    // mode of the Windows console (conhost does not turn it on by default, so
    // without this every log line is prefixed with raw escape codes).
    // Safe to call several times.
    void enableAnsiSequences();

    // Unblock a thread sitting in std::getline(std::cin, ...).
    // Neither std::cin.setstate() nor a signal wakes a blocking read, so the
    // underlying handle/descriptor has to be interrupted. Only meant to be
    // used while shutting down: stdin is unusable afterwards.
    void interruptStdin();
}

#endif // EXNG_CONSOLE_HPP
