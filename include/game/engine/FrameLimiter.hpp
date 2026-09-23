#pragma once

#include <chrono>

namespace game::engine {

// Limits rendering to a maximum FPS. A value <= 0 disables the limit.
// It never adds a delay when the previous frame already took too long.
class FrameLimiter {
public:
    using Clock = std::chrono::steady_clock;

    explicit FrameLimiter(double maxFps = 0.0);

    void setMaxFps(double maxFps);
    double maxFps() const noexcept;

    void beginFrame();
    void endFrame();

private:
    double maxFps_ = 0.0;
    Clock::duration frameDuration_{};
    Clock::time_point nextDeadline_{};
    bool hasDeadline_ = false;
};

} // namespace game::engine
