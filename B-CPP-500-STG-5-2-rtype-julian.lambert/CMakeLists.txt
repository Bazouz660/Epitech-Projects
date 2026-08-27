# Specify the minimum required version of CMake
cmake_minimum_required(VERSION 3.16)

# Set the project name
project(R-Type LANGUAGES CXX)

# Set the C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Default to a Release build when no configuration is provided
if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

# Set the project version
set(PROJECT_VERSION_MAJOR alpha-4)
set(PROJECT_VERSION_MINOR 0)
set(PROJECT_VERSION_PATCH 2)
set(PROJECT_VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH})

# Set the CPack package version
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})

# ---------------------------------------------------------------------------
# Dependencies
# ---------------------------------------------------------------------------
# SFML is fetched and built from source: it works out of the box on both
# Windows (MinGW / MSVC) and Linux, and avoids relying on a system-wide
# package manager.
include(FetchContent)

set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_DOC OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_TEST_SUITE OFF CACHE BOOL "" FORCE)
set(SFML_USE_STATIC_STD_LIBS ON CACHE BOOL "" FORCE)

FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.2
    GIT_SHALLOW ON
)
FetchContent_MakeAvailable(SFML)

if (WIN32 AND CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    # Fully static link: without it the binaries need libgcc_s, libstdc++ and
    # libwinpthread next to them, which the release archive does not ship
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++ -static")
endif()

# SFML links OpenAL dynamically on Windows and ships the dll in its extlibs:
# it has to travel with the binaries or the client cannot start.
if (WIN32)
    if (CMAKE_SIZEOF_VOID_P EQUAL 8)
        set(OPENAL_DLL_ARCH "x64")
    else()
        set(OPENAL_DLL_ARCH "x86")
    endif()
    set(OPENAL_DLL "${sfml_SOURCE_DIR}/extlibs/bin/${OPENAL_DLL_ARCH}/openal32.dll")

    if (NOT EXISTS "${OPENAL_DLL}")
        message(FATAL_ERROR "openal32.dll not found in the SFML sources: ${OPENAL_DLL}")
    endif()

    install(FILES "${OPENAL_DLL}" DESTINATION .)
endif()

# Add the client and server subdirectories
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(engine)
add_subdirectory(client)
add_subdirectory(server)

# ---------------------------------------------------------------------------
# Packaging
# ---------------------------------------------------------------------------
set(CPACK_PACKAGE_VENDOR "Youpi-Corp")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "R-Type is a multiplayer game where you can play with your friends")
set(CPACK_PACKAGE_CONTACT "Youpi-Corp@youpi.fr")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE.md")
set(CPACK_PACKAGE_FILE_NAME "r-type-${PROJECT_VERSION}")
set(CPACK_INCLUDE_TOPLEVEL_DIRECTORY OFF)
set(CPACK_OUTPUT_FILE_PREFIX "package")

if(WIN32)
    set(CPACK_GENERATOR "ZIP")
else()
    set(CPACK_GENERATOR "TGZ")
endif()

install(TARGETS r-type_client RUNTIME DESTINATION .)
install(TARGETS r-type_server RUNTIME DESTINATION .)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/asset/ DESTINATION asset)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/config.ini DESTINATION .)

# Include CPack for packaging
include(CPack)
