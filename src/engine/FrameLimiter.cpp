#include "game/engine/FrameLimiter.hpp"

#include <algorithm>
#include <thread>

namespace game::engine {

FrameLimiter::FrameLimiter(double maxFps)
{
    setMaxFps(maxFps);
}

void FrameLimiter::setMaxFps(double maxFps)
{
    maxFps_ = std::max(0.0, maxFps);

    if (maxFps_ > 0.0) {
        frameDuration_ = std::chrono::duration_cast<Clock::duration>(
            std::chrono::duration<double>(1.0 / maxFps_));
    } else {
        frameDuration_ = Clock::duration::zero();
    }

    hasDeadline_ = false;
}

double FrameLimiter::maxFps() const noexcept
{
    return maxFps_;
}

void FrameLimiter::beginFrame()
{
    if (maxFps_ > 0.0 && hasDeadline_) {
        const auto now = Clock::now();
        if (nextDeadline_ > now) {
            std::this_thread::sleep_until(nextDeadline_);
        }
    }

    if (maxFps_ > 0.0) {
        if (!hasDeadline_) {
            nextDeadline_ = Clock::now();
            hasDeadline_ = true;
        }
    }
}

void FrameLimiter::endFrame()
{
    if (maxFps_ <= 0.0) {
        return;
    }

    nextDeadline_ += frameDuration_;

    // Rendering took longer than the budget: continue immediately instead
    // of accumulating an ever-growing delay.
    const auto now = Clock::now();
    if (nextDeadline_ < now) {
        nextDeadline_ = now;
    }
}

} // namespace game::engine
