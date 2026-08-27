cmake_minimum_required(VERSION 3.10)
project(raytracer)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

set(CMAKE_CXX_STANDARD 20)

include_directories("includes")

file(GLOB_RECURSE header_files "src/*.hpp")
foreach(_headerFile ${header_files})
    get_filename_component(_dir ${_headerFile} DIRECTORY)
    include_directories(${_dir})
endforeach()

# Add the source files
file(GLOB_RECURSE SOURCE_FILES "${PROJECT_SOURCE_DIR}/src/*.cpp")

# Create the executable
add_executable(raytracer ${SOURCE_FILES})

target_link_libraries(raytracer config++ pthread)

# Set the output directory for the executable
set_target_properties(raytracer PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
