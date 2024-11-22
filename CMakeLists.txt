cmake_minimum_required(VERSION 3.28)
project(clock)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib
        GIT_TAG c1ab645ca298a2801097931d1079b10ff7eb9df8)
FetchContent_MakeAvailable(raylib)

if (WIN32)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
    set(EXECUTABLE_TYPE WIN32
            src/state.h
            src/state.cpp)
endif ()

add_executable(clock ${EXECUTABLE_TYPE}
        src/main.cpp
        src/application.h
        src/application.cpp
        src/config.h
        src/config.cpp
        src/functions.h
        src/clock.h
        src/clock.cpp
        src/state.h
        src/state.cpp)
target_link_libraries(clock raylib)
target_include_directories(clock PRIVATE external)

add_custom_target(
        CopyFaces
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/faces
        $<TARGET_FILE_DIR:clock>/
)
add_dependencies(clock CopyFaces)
