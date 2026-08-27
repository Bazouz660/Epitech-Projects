# Specify the minimum required version of CMake
cmake_minimum_required(VERSION 3.5)

include(FetchContent)
include(ExternalProject)

# Clone and bootstrap vcpkg if it doesn't exist
if (NOT EXISTS ${CMAKE_BINARY_DIR}/vcpkg)
    execute_process(COMMAND git clone https://github.com/Microsoft/vcpkg.git ${CMAKE_BINARY_DIR}/vcpkg)
    if (WIN32)
        execute_process(COMMAND ${CMAKE_BINARY_DIR}/vcpkg/bootstrap-vcpkg.bat)
    elseif(UNIX)
        execute_process(COMMAND ${CMAKE_BINARY_DIR}/vcpkg/bootstrap-vcpkg.sh)
    endif()
endif()

# Install the required packages

if (WIN32)
    set(TRIPLET "x64-mingw-static")
elseif(UNIX)
    set(TRIPLET "x64-linux")
endif()

# Install system dependencies (autoconf, automake, libtool, etc.)
execute_process(COMMAND ${CMAKE_BINARY_DIR}/vcpkg/vcpkg install xcb-util-m4 --host-triplet=${TRIPLET} --triplet=${TRIPLET})

execute_process(COMMAND ${CMAKE_BINARY_DIR}/vcpkg/vcpkg install sfml --host-triplet=${TRIPLET} --triplet=${TRIPLET})

# Set the path to the vcpkg toolchain file
set(VCPKG_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/build/vcpkg" CACHE STRING "")
set(VCPKG_TARGET_TRIPLET ${TRIPLET} CACHE STRING "")
set(VCPKG_HOST_TRIPLET ${TRIPLET} CACHE STRING "")
set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT_DIR}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")

# Set the project name
project(R-Type)

# Set the C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)

if (WIN32)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++ -static")
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

# Find SFML package
set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML COMPONENTS graphics window system network audio REQUIRED)

# Add the client and server subdirectories
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(engine)
add_subdirectory(client)
add_subdirectory(server)

# Set the CPack package information
set(CPACK_PACKAGE_VENDOR "Youpi-Corp")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "R-Type is a multiplayer game where you can play with your friends")
set(CPACK_PACKAGE_CONTACT "Youpi-Corp@youpi.fr")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE.md")

# Set the NSIS download URL and add the NSIS external project (for Windows)
if(WIN32)
    ExternalProject_Add(
        NSIS_project
        URL https://sourceforge.net/projects/nsis/files/NSIS%203/3.08/nsis-3.08.zip/download?use_mirror=freefr
        PREFIX ${CMAKE_BINARY_DIR}/NSIS
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        INSTALL_COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_BINARY_DIR}/NSIS/src/NSIS_project ${CMAKE_BINARY_DIR}/NSIS-install
        TIMEOUT 60
        DOWNLOAD_EXTRACT_TIMESTAMP 1
    )
    set(CPACK_NSIS_MUI_ICON "${CMAKE_SOURCE_DIR}/asset/icon/youpi.ico")
    set(CPACK_NSIS_MUI_UNIICON "${CMAKE_SOURCE_DIR}/asset/icon/youpi.ico")
    set(CPACK_NSIS_PACKAGE_INSTALL_DIRECTORY ${CMAKE_BINARY_DIR}/NSIS-install)
    set(CPACK_NSIS_EXECUTABLE "${CMAKE_BINARY_DIR}/NSIS-install/bin/makensis.exe")
    # add option to choose to create a desktop shortcut
    set(CPACK_NSIS_ENABLE_UNINSTALL_BEFORE_INSTALL ON)
    set(CPACK_GENERATOR "ZIP;NSIS")
    set(CPACK_PACKAGE_FILE_NAME "r-type-${PROJECT_VERSION}")
    set(CPACK_INCLUDE_TOPLEVEL_DIRECTORY OFF)
    set(CPACK_OUTPUT_FILE_PREFIX "package")
    install(TARGETS r-type_client RUNTIME DESTINATION .)
    install(TARGETS r-type_server RUNTIME DESTINATION .)
    install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/asset/ DESTINATION asset)
elseif(UNIX)
    set(CPACK_GENERATOR "TGZ")
    set(CPACK_PACKAGE_FILE_NAME "r-type-${PROJECT_VERSION}")
    set(CPACK_INCLUDE_TOPLEVEL_DIRECTORY OFF)
    set(CPACK_OUTPUT_FILE_PREFIX "package")
    install(TARGETS r-type_client RUNTIME DESTINATION .)
    install(TARGETS r-type_server RUNTIME DESTINATION .)
    install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/asset/ DESTINATION asset)
endif()

# Include CPack for packaging
include(CPack)
