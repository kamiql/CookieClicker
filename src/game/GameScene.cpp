#include "game/GameScene.hpp"

#include <GLFW/glfw3.h>

GameScene::GameScene() :
    cookieTexture_(std::filesystem::path(ASSET_DIR) / "textures" / "cookie.png"),
    backgroundTexture_(std::filesystem::path(ASSET_DIR) / "textures" / "background.png")
{}

void GameScene::update(GLFWwindow *window, SaveData *data) {
}

void GameScene::render(Renderer &renderer) const {
    renderer.drawRectangle(
        0.0f, 0.0f,
        1.0f, 1.0f,
        { 1.0f, 1.0f, 1.0f, 1.0f },
        nullptr,
        backgroundTexture_.id()
    );

    renderer.drawCircle(
        {0.5f, 0.5f},
        0.22f,
        { 0.2f, 0.2f, 0.2f, 0.4f },
        64
    );

    renderer.drawCircle(
        {0.5f, 0.5f},
        0.15f,
        { 1.0f, 1.0f, 1.0f, 1.0f },
        64,
        nullptr,
        cookieTexture_.id()
    );
}
