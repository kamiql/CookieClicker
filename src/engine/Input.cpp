#include "game/engine/Input.hpp"

namespace game::engine {

bool Input::pollEvents()
{
    SDL_Event event{};

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_EVENT_QUIT:
        case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
            quitRequested_ = true;
            break;

        case SDL_EVENT_KEY_DOWN:
            handleKeyDown(event.key.key, event.key.repeat);
            break;

        case SDL_EVENT_KEY_UP:
            handleKeyUp(event.key.key);
            break;

        default:
            break;
        }
    }

    return !quitRequested_;
}

void Input::handleKeyDown(SDL_Keycode key, bool repeat)
{
    switch (key) {
    case SDLK_A:
    case SDLK_LEFT:
        state_.moveLeft = true;
        break;

    case SDLK_D:
    case SDLK_RIGHT:
        state_.moveRight = true;
        break;

    case SDLK_W:
    case SDLK_UP:
        state_.moveUp = true;
        break;

    case SDLK_S:
    case SDLK_DOWN:
        state_.moveDown = true;
        break;

    case SDLK_P:
        if (!repeat) {
            pendingEvents_.push_back({InputEventType::PausePressed});
        }
        break;

    case SDLK_SPACE:
        if (!repeat) {
            pendingEvents_.push_back({InputEventType::JumpPressed});
        }
        break;

    case SDLK_F:
        if (!repeat) {
            pendingEvents_.push_back({InputEventType::FirePressed});
        }
        break;

    default:
        break;
    }
}

void Input::handleKeyUp(SDL_Keycode key)
{
    switch (key) {
    case SDLK_A:
    case SDLK_LEFT:
        state_.moveLeft = false;
        break;

    case SDLK_D:
    case SDLK_RIGHT:
        state_.moveRight = false;
        break;

    case SDLK_W:
    case SDLK_UP:
        state_.moveUp = false;
        break;

    case SDLK_S:
    case SDLK_DOWN:
        state_.moveDown = false;
        break;

    default:
        break;
    }
}

const InputState& Input::state() const noexcept
{
    return state_;
}

const std::vector<InputEvent>& Input::pendingEvents() const noexcept
{
    return pendingEvents_;
}

void Input::clearTransientEvents() noexcept
{
    pendingEvents_.clear();
}

} // namespace game::engine
