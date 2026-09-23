#pragma once

#include <SDL3/SDL.h>

#include <vector>

namespace game::engine {

enum class InputEventType {
    JumpPressed,
    PausePressed,
    FirePressed
};

struct InputEvent {
    InputEventType type;
};

struct InputState {
    bool moveLeft = false;
    bool moveRight = false;
    bool moveUp = false;
    bool moveDown = false;
};

class Input {
public:
    // Polls OS/window events. Returns false when the application should stop.
    bool pollEvents();

    const InputState& state() const noexcept;
    const std::vector<InputEvent>& pendingEvents() const noexcept;

    // Clears one-shot events after at least one game tick consumed them.
    void clearTransientEvents() noexcept;

private:
    void handleKeyDown(SDL_Keycode key, bool repeat);
    void handleKeyUp(SDL_Keycode key);

    bool quitRequested_ = false;
    InputState state_{};
    std::vector<InputEvent> pendingEvents_;
};

} // namespace game::engine
