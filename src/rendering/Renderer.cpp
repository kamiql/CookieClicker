#include "game/rendering/Renderer.hpp"

#include <algorithm>

namespace game::rendering {

Renderer::Renderer(engine::RenderContext& context)
    : context_(context)
{
}

void Renderer::render(const game::RenderSnapshot& snapshot)
{
    SDL_Renderer* renderer = context_.renderer();

    const float scaleX = static_cast<float>(context_.outputWidth()) / 960.0f;
    const float scaleY = static_cast<float>(context_.outputHeight()) / 540.0f;

    // A subtle floor makes the world bounds visible without introducing
    // renderer-specific game logic.
    SDL_SetRenderDrawColor(renderer, 35, 43, 58, 255);
    SDL_FRect floorRect{
        0.0f,
        500.0f * scaleY,
        static_cast<float>(context_.outputWidth()),
        40.0f * scaleY};
    SDL_RenderFillRect(renderer, &floorRect);

    const auto& p = snapshot.playerPosition;
    SDL_FRect playerRect{
        p.x * scaleX,
        p.y * scaleY,
        snapshot.playerSize * scaleX,
        snapshot.playerSize * scaleY};

    if (snapshot.paused) {
        SDL_SetRenderDrawColor(renderer, 224, 167, 72, 255);
    } else {
        SDL_SetRenderDrawColor(renderer, 70, 170, 255, 255);
    }

    SDL_RenderFillRect(renderer, &playerRect);
}

} // namespace game::rendering
