#pragma once

#include "game/engine/Input.hpp"
#include "game/game/GameState.hpp"

#include <vector>

namespace game {

class Game {
public:
    Game(float worldWidth = 960.0f, float worldHeight = 540.0f);

    void tick(
        float fixedDeltaTime,
        const engine::InputState& input,
        const std::vector<engine::InputEvent>& events);

    RenderSnapshot createRenderSnapshot(float interpolation) const;

    const GameState& state() const noexcept;

private:
    void processInput(const engine::InputState& input);
    void processEvents(const std::vector<engine::InputEvent>& events);
    void updatePlayer(float fixedDeltaTime);
    void clampPlayerToWorld();

    GameState previousState_{};
    GameState currentState_{};
    float worldWidth_ = 960.0f;
    float worldHeight_ = 540.0f;
    float playerSpeed_ = 220.0f;
};

} // namespace game
