/*
** EPITECH PROJECT, 2023
** B-CPP-500-STG-5-2-rtype-julian.lambert
** File description:
** paths
*/

#include "paths.hpp"

#include <filesystem>
#include <vector>

#ifdef _WIN32
    #ifndef WIN32_LEAN_AND_MEAN
        #define WIN32_LEAN_AND_MEAN
    #endif
    #ifndef NOMINMAX
        // windows.h defines min/max as macros, which breaks std::min/std::max
        #define NOMINMAX
    #endif
    #include <windows.h>
#elif defined(__linux__)
    #include <unistd.h>
    #include <limits.h>
#endif

namespace exng::paths {

    namespace {

        std::string computeExecutableDir()
        {
        #ifdef _WIN32
            std::wstring buffer(MAX_PATH, L'\0');
            DWORD size = 0;
            while (true) {
                size = GetModuleFileNameW(nullptr, buffer.data(), static_cast<DWORD>(buffer.size()));
                if (size == 0)
                    return std::filesystem::current_path().string();
                if (size < buffer.size())
                    break;
                buffer.resize(buffer.size() * 2);
            }
            buffer.resize(size);
            return std::filesystem::path(buffer).parent_path().string();
        #elif defined(__linux__)
            std::vector<char> buffer(PATH_MAX);
            ssize_t size = readlink("/proc/self/exe", buffer.data(), buffer.size() - 1);
            if (size <= 0)
                return std::filesystem::current_path().string();
            buffer[static_cast<std::size_t>(size)] = '\0';
            return std::filesystem::path(buffer.data()).parent_path().string();
        #else
            return std::filesystem::current_path().string();
        #endif
        }

        // Candidate roots, most specific first.
        const std::vector<std::filesystem::path> &searchRoots()
        {
            static const std::vector<std::filesystem::path> roots = []() {
                std::filesystem::path exe(executableDir());
                std::vector<std::filesystem::path> result;

                result.push_back(exe);
                result.push_back(exe / "..");
                result.push_back(exe / ".." / "..");
                result.push_back(exe / ".." / ".." / "..");

                std::error_code ec;
                std::filesystem::path cwd = std::filesystem::current_path(ec);
                if (!ec)
                    result.push_back(cwd);

                return result;
            }();
            return roots;
        }
    }

    const std::string &executableDir()
    {
        static const std::string dir = computeExecutableDir();
        return dir;
    }

    std::string resolve(const std::string &relativePath)
    {
        std::filesystem::path relative(relativePath);

        if (relative.is_absolute())
            return relativePath;

        std::error_code ec;
        for (const auto &root : searchRoots()) {
            std::filesystem::path candidate = root / relative;
            if (std::filesystem::exists(candidate, ec))
                return std::filesystem::weakly_canonical(candidate, ec).string();
        }

        // Nothing on disk yet: default to a path next to the executable so
        // that files we may have to create (config.ini) land in a sane place.
        return (searchRoots().front() / relative).string();
    }
}
