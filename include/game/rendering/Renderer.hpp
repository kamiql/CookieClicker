#pragma once

#include "game/engine/RenderContext.hpp"
#include "game/game/GameState.hpp"

namespace game::rendering {

class Renderer {
public:
    explicit Renderer(engine::RenderContext& context);

    void render(const game::RenderSnapshot& snapshot);

private:
    engine::RenderContext& context_;
};

} // namespace game::rendering
