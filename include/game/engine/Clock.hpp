#pragma once

#include <chrono>

namespace game::engine {

class Clock {
public:
    using clock = std::chrono::steady_clock;
    using time_point = clock::time_point;

    static time_point now() noexcept;
    static double secondsBetween(time_point from, time_point to) noexcept;
};

} // namespace game::engine
