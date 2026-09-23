#pragma once

#include "game/engine/FrameLimiter.hpp"
#include "game/engine/Input.hpp"

#include <functional>
#include <vector>

namespace game::engine {

class GameLoop {
public:
    using TickCallback = std::function<void(
        float fixedDeltaTime,
        const InputState& input,
        const std::vector<InputEvent>& events)>;

    using RenderCallback = std::function<void(float interpolation)>;

    GameLoop(double tickRate = 60.0, double maxRenderFps = 0.0);

    void run(
        Input& input,
        const TickCallback& onTick,
        const RenderCallback& onRender);

    void requestStop() noexcept;
    bool isRunning() const noexcept;

    void setTickRate(double tickRate);
    void setMaxRenderFps(double maxFps);

private:
    double tickRate_ = 60.0;
    double fixedDeltaTime_ = 1.0 / 60.0;
    int maxTicksPerFrame_ = 8;
    bool running_ = false;
    FrameLimiter frameLimiter_;
};

} // namespace game::engine
