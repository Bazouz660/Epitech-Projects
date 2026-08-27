/*
** EPITECH PROJECT, 2023
** B-CPP-500-STG-5-2-rtype-julian.lambert
** File description:
** paths
*/

#ifndef EXNG_PATHS_HPP
#define EXNG_PATHS_HPP

#include <string>

namespace exng::paths {

    // Absolute path of the directory containing the running executable.
    // Falls back to the current working directory when it cannot be determined.
    const std::string &executableDir();

    // Resolve a path that is relative to the game root (the folder holding
    // "asset/" and "config.ini").
    //
    // The game root is looked up next to the executable first, then a few
    // levels above it (so that running r-type_client straight out of
    // build/client/ still finds the assets), and finally in the current
    // working directory. The relative path is returned untouched when nothing
    // matches, the path next to the executable is returned so that files we
    // have to create (config.ini) land in a predictable place.
    std::string resolve(const std::string &relativePath);
}

#endif // EXNG_PATHS_HPP
