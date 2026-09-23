#pragma once

namespace game {

struct Vec2 {
    float x = 0.0f;
    float y = 0.0f;
};

struct PlayerState {
    Vec2 position{};
    Vec2 velocity{};
    float size = 32.0f;
};

struct GameState {
    PlayerState player{};
    int score = 0;
    bool paused = false;
};

// Data-only presentation object. It contains no SDL/OpenGL resources.
struct RenderSnapshot {
    Vec2 playerPosition{};
    float playerSize = 32.0f;
    int score = 0;
    bool paused = false;
};

} // namespace game
