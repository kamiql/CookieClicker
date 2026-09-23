#pragma once

#include "game/engine/GameLoop.hpp"
#include "game/engine/Input.hpp"
#include "game/engine/RenderContext.hpp"
#include "game/game/Game.hpp"
#include "game/rendering/Renderer.hpp"

namespace gameapp {

class Application {
public:
    Application();
    int run();

private:
    game::engine::RenderContext renderContext_;
    game::engine::Input input_;
    game::Game game_;
    game::rendering::Renderer renderer_;
    game::engine::GameLoop gameLoop_;
};

} // namespace gameapp
