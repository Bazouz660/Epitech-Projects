set(EXECUTABLE_NAME r-type_client)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp")
add_executable(${EXECUTABLE_NAME} ${SOURCES})

target_include_directories(${EXECUTABLE_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/client/include)
target_include_directories(${EXECUTABLE_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/engine/include)
target_include_directories(${EXECUTABLE_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/engine/src)
# Find all subfolders in engine/src and add them to include directories
file(GLOB_RECURSE header_files CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/engine/src/*.hpp)
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

    # SFML loads OpenAL at runtime: the dll must sit next to whichever copy of
    # the client gets started
    add_custom_command(TARGET ${EXECUTABLE_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${OPENAL_DLL}" "${CMAKE_BINARY_DIR}/client/openal32.dll"
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${OPENAL_DLL}" "${CMAKE_SOURCE_DIR}/openal32.dll")
else ()
    add_custom_command(TARGET ${EXECUTABLE_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_BINARY_DIR}/client/${EXECUTABLE_NAME}"
            "${CMAKE_SOURCE_DIR}/${EXECUTABLE_NAME}")
endif ()
