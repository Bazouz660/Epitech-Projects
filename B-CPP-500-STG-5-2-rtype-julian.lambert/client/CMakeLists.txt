set(EXECUTABLE_NAME r-type_client)

file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(${EXECUTABLE_NAME} ${SOURCES})

target_include_directories(${EXECUTABLE_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/client/include)
target_include_directories(${EXECUTABLE_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/engine/include)
target_include_directories(${EXECUTABLE_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/engine/src)
# Find all subfolders in engine/src and add them to include directories
file(GLOB_RECURSE header_files ${CMAKE_SOURCE_DIR}/engine/src/*.hpp)
foreach(_headerFile ${header_files})
    get_filename_component(_dir ${_headerFile} DIRECTORY)
    target_include_directories(${EXECUTABLE_NAME} PRIVATE ${_dir})
endforeach()

# target dependencies (sfml)
target_include_directories(${EXECUTABLE_NAME} PRIVATE ${SFML_INCLUDE_DIR})

target_link_libraries(${EXECUTABLE_NAME} sfml-system sfml-window sfml-graphics sfml-network sfml-audio r-type_engine)

# Copy executable to root directory, replace if already exists, add .exe extension on windows
if (WIN32)
    add_custom_command(TARGET ${EXECUTABLE_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_BINARY_DIR}/client/${EXECUTABLE_NAME}.exe"
            "${CMAKE_SOURCE_DIR}/${EXECUTABLE_NAME}.exe")
else ()
    add_custom_command(TARGET ${EXECUTABLE_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_BINARY_DIR}/client/${EXECUTABLE_NAME}"
            "${CMAKE_SOURCE_DIR}/${EXECUTABLE_NAME}")
endif ()
