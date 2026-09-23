#include "game/engine/Clock.hpp"

namespace game::engine {

Clock::time_point Clock::now() noexcept
{
    return clock::now();
}

double Clock::secondsBetween(time_point from, time_point to) noexcept
{
    return std::chrono::duration<double>(to - from).count();
}

} // namespace game::engine
