#include "game/engine/GameLoop.hpp"

#include "game/engine/Clock.hpp"

#include <algorithm>
#include <stdexcept>

namespace game::engine {

GameLoop::GameLoop(double tickRate, double maxRenderFps)
    : frameLimiter_(maxRenderFps)
{
    setTickRate(tickRate);
}

void GameLoop::setTickRate(double tickRate)
{
    if (tickRate <= 0.0) {
        throw std::invalid_argument("tickRate must be greater than zero");
    }

    tickRate_ = tickRate;
    fixedDeltaTime_ = 1.0 / tickRate_;
}

void GameLoop::setMaxRenderFps(double maxFps)
{
    frameLimiter_.setMaxFps(maxFps);
}

void GameLoop::run(
    Input& input,
    const TickCallback& onTick,
    const RenderCallback& onRender)
{
    running_ = true;
    double accumulator = 0.0;
    auto previousTime = Clock::now();

    static const std::vector<InputEvent> noEvents;

    while (running_) {
        // This only waits when the configured maximum FPS would otherwise
        // be exceeded. It does not slow down an already overloaded machine.
        frameLimiter_.beginFrame();

        if (!input.pollEvents()) {
            running_ = false;
            break;
        }

        const auto currentTime = Clock::now();
        double elapsed = Clock::secondsBetween(previousTime, currentTime);
        previousTime = currentTime;

        // Avoid a huge simulation jump after a breakpoint or a suspended app.
        elapsed = std::clamp(elapsed, 0.0, 0.25);
        accumulator += elapsed;

        int ticksThisFrame = 0;
        bool deliveredTransientEvents = false;

        while (accumulator >= fixedDeltaTime_ &&
               ticksThisFrame < maxTicksPerFrame_) {
            const auto& events = deliveredTransientEvents
                ? noEvents
                : input.pendingEvents();

            onTick(
                static_cast<float>(fixedDeltaTime_),
                input.state(),
                events);

            deliveredTransientEvents = true;
            accumulator -= fixedDeltaTime_;
            ++ticksThisFrame;
        }

        if (deliveredTransientEvents) {
            input.clearTransientEvents();
        }

        // The interpolation value describes the fraction towards the next
        // fixed tick. Rendering remains independent of the tick frequency.
        const float interpolation = static_cast<float>(
            accumulator / fixedDeltaTime_);

        onRender(interpolation);
        frameLimiter_.endFrame();

        // If the simulation cannot keep up, do not enter an endless catch-up
        // loop. Dropping excess accumulated time keeps the app responsive.
        if (ticksThisFrame == maxTicksPerFrame_ &&
            accumulator >= fixedDeltaTime_) {
            accumulator = 0.0;
        }
    }
}

void GameLoop::requestStop() noexcept
{
    running_ = false;
}

bool GameLoop::isRunning() const noexcept
{
    return running_;
}

} // namespace game::engine
