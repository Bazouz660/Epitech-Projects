/*
** EPITECH PROJECT, 2023
** B-CPP-500-STG-5-2-rtype-julian.lambert
** File description:
** console
*/

#include "console.hpp"

#include <iostream>

#ifdef _WIN32
    #ifndef WIN32_LEAN_AND_MEAN
        #define WIN32_LEAN_AND_MEAN
    #endif
    #ifndef NOMINMAX
        // windows.h defines min/max as macros, which breaks std::min/std::max
        #define NOMINMAX
    #endif
    #include <windows.h>

    #ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
        #define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
    #endif
#else
    #include <unistd.h>
#endif

namespace exng::console {

    void enableAnsiSequences()
    {
    #ifdef _WIN32
        static bool done = false;
        if (done)
            return;
        done = true;

        SetConsoleOutputCP(CP_UTF8);

        for (DWORD handleId : {STD_OUTPUT_HANDLE, STD_ERROR_HANDLE}) {
            HANDLE handle = GetStdHandle(handleId);
            if (handle == INVALID_HANDLE_VALUE || handle == nullptr)
                continue;

            DWORD mode = 0;
            if (!GetConsoleMode(handle, &mode))
                continue; // redirected to a file or a pipe: nothing to enable

            SetConsoleMode(handle, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
        }
    #endif
    }

    void interruptStdin()
    {
        static bool done = false;
        if (done)
            return;
        done = true;

        std::cin.setstate(std::ios_base::eofbit);

    #ifdef _WIN32
        HANDLE handle = GetStdHandle(STD_INPUT_HANDLE);
        if (handle != INVALID_HANDLE_VALUE && handle != nullptr) {
            CancelIoEx(handle, nullptr);
            CloseHandle(handle);
        }
    #else
        ::close(STDIN_FILENO);
    #endif
    }
}
