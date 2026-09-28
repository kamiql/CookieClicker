cmake_minimum_required(VERSION 3.16)
project(CookieClicker LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(glfw3 CONFIG REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_path(STB_INCLUDE_DIR stb_image.h REQUIRED)

add_executable(CookieClicker
        src/main.cpp
        src/rendering/Shader.cpp
        src/rendering/Renderer.cpp
        src/game/GameScene.cpp
        src/game/SaveManager.cpp
)

target_include_directories(CookieClicker PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
        "${STB_INCLUDE_DIR}"
)

target_compile_definitions(CookieClicker PRIVATE
        SHADER_DIR="${CMAKE_CURRENT_SOURCE_DIR}/shader"
        ASSET_DIR="${CMAKE_CURRENT_SOURCE_DIR}/assets"
)

target_link_libraries(CookieClicker PRIVATE
        glfw
        OpenGL::GL
        GLEW::GLEW
        nlohmann_json::nlohmann_json
)

target_sources(CookieClicker PRIVATE
        src/rendering/Texture2D.cpp
)