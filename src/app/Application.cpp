#include "game/app/Application.hpp"

namespace gameapp {

Application::Application()
    : renderContext_("Simple 2D Tick Game", 960, 540)
    , renderer_(renderContext_)
    // 60 game ticks per second; 0 means unlimited rendering.
    , gameLoop_(60.0, 0.0)
{
}

int Application::run()
{
    gameLoop_.run(
        input_,
        [this](float fixedDeltaTime,
               const game::engine::InputState& input,
               const std::vector<game::engine::InputEvent>& events) {
            game_.tick(fixedDeltaTime, input, events);
        },
        [this](float interpolation) {
            renderContext_.beginFrame();
            renderer_.render(game_.createRenderSnapshot(interpolation));
            renderContext_.endFrame();
        });

    return 0;
}

} // namespace gameapp
