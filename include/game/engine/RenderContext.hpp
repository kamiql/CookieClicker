#pragma once

#include <SDL3/SDL.h>

namespace game::engine {

class RenderContext {
public:
    RenderContext(const char* title, int width, int height);
    ~RenderContext();

    RenderContext(const RenderContext&) = delete;
    RenderContext& operator=(const RenderContext&) = delete;

    void beginFrame();
    void endFrame();

    SDL_Window* window() const noexcept;
    SDL_Renderer* renderer() const noexcept;

    int outputWidth() const noexcept;
    int outputHeight() const noexcept;

private:
    SDL_Window* window_ = nullptr;
    SDL_Renderer* renderer_ = nullptr;
    int outputWidth_ = 0;
    int outputHeight_ = 0;
};

} // namespace game::engine
