cmake_minimum_required(VERSION 3.20)

project(simple2d
        VERSION 1.0
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(SDL3 CONFIG REQUIRED)

add_executable(simple2d
        src/main.cpp

        src/app/Application.cpp

        src/engine/Clock.cpp
        src/engine/FrameLimiter.cpp
        src/engine/GameLoop.cpp
        src/engine/Input.cpp
        src/engine/RenderContext.cpp

        src/game/Game.cpp

        src/rendering/Renderer.cpp
)

target_include_directories(simple2d
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(simple2d
        PRIVATE
        SDL3::SDL3
)