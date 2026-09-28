#pragma once

#include "game/SaveManager.hpp"
#include "rendering/Renderer.hpp"
#include "rendering/Texture2D.hpp"

struct GLFWwindow;

class GameScene {
public:
    GameScene();

    void update(GLFWwindow* window, SaveData* data);
    void render(Renderer& renderer) const;

private:
    Texture2D cookieTexture_;
    Texture2D backgroundTexture_;
};