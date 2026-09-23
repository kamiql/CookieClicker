#include "game/engine/RenderContext.hpp"

#include <stdexcept>
#include <string>

namespace game::engine {

RenderContext::RenderContext(const char* title, int width, int height)
{
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        throw std::runtime_error(
            std::string("SDL_Init failed: ") + SDL_GetError());
    }

    window_ = SDL_CreateWindow(
        title,
        width,
        height,
        SDL_WINDOW_RESIZABLE);

    if (!window_) {
        SDL_Quit();
        throw std::runtime_error(
            std::string("SDL_CreateWindow failed: ") + SDL_GetError());
    }

    renderer_ = SDL_CreateRenderer(window_, nullptr);

    if (!renderer_) {
        SDL_DestroyWindow(window_);
        window_ = nullptr;
        SDL_Quit();
        throw std::runtime_error(
            std::string("SDL_CreateRenderer failed: ") + SDL_GetError());
    }

    SDL_GetRenderOutputSize(renderer_, &outputWidth_, &outputHeight_);
}

RenderContext::~RenderContext()
{
    if (renderer_) {
        SDL_DestroyRenderer(renderer_);
    }

    if (window_) {
        SDL_DestroyWindow(window_);
    }

    SDL_Quit();
}

void RenderContext::beginFrame()
{
    SDL_GetRenderOutputSize(renderer_, &outputWidth_, &outputHeight_);

    SDL_SetRenderDrawColor(renderer_, 18, 22, 31, 255);
    SDL_RenderClear(renderer_);
}

void RenderContext::endFrame()
{
    SDL_RenderPresent(renderer_);
}

SDL_Window* RenderContext::window() const noexcept
{
    return window_;
}

SDL_Renderer* RenderContext::renderer() const noexcept
{
    return renderer_;
}

int RenderContext::outputWidth() const noexcept
{
    return outputWidth_;
}

int RenderContext::outputHeight() const noexcept
{
    return outputHeight_;
}

} // namespace game::engine
