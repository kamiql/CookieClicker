#include "game/game/Game.hpp"

#include <algorithm>

namespace game {

Game::Game(float worldWidth, float worldHeight)
    : worldWidth_(worldWidth)
    , worldHeight_(worldHeight)
{
    currentState_.player.position = {
        worldWidth_ * 0.5f - currentState_.player.size * 0.5f,
        worldHeight_ * 0.5f - currentState_.player.size * 0.5f};
    previousState_ = currentState_;
}

void Game::tick(
    float fixedDeltaTime,
    const engine::InputState& input,
    const std::vector<engine::InputEvent>& events)
{
    // The snapshot before this tick is used for render interpolation.
    previousState_ = currentState_;

    processInput(input);
    processEvents(events);

    if (!currentState_.paused) {
        updatePlayer(fixedDeltaTime);
        clampPlayerToWorld();
    }
}

void Game::processInput(const engine::InputState& input)
{
    currentState_.player.velocity = {};

    if (input.moveLeft) {
        currentState_.player.velocity.x -= playerSpeed_;
    }
    if (input.moveRight) {
        currentState_.player.velocity.x += playerSpeed_;
    }
    if (input.moveUp) {
        currentState_.player.velocity.y -= playerSpeed_;
    }
    if (input.moveDown) {
        currentState_.player.velocity.y += playerSpeed_;
    }
}

void Game::processEvents(const std::vector<engine::InputEvent>& events)
{
    for (const auto& event : events) {
        switch (event.type) {
        case engine::InputEventType::PausePressed:
            currentState_.paused = !currentState_.paused;
            break;

        case engine::InputEventType::JumpPressed:
        case engine::InputEventType::FirePressed:
            // Placeholder for future game actions.
            ++currentState_.score;
            break;
        }
    }
}

void Game::updatePlayer(float fixedDeltaTime)
{
    currentState_.player.position.x +=
        currentState_.player.velocity.x * fixedDeltaTime;
    currentState_.player.position.y +=
        currentState_.player.velocity.y * fixedDeltaTime;
}

void Game::clampPlayerToWorld()
{
    const float maxX = worldWidth_ - currentState_.player.size;
    const float maxY = worldHeight_ - currentState_.player.size;

    currentState_.player.position.x = std::clamp(
        currentState_.player.position.x, 0.0f, maxX);
    currentState_.player.position.y = std::clamp(
        currentState_.player.position.y, 0.0f, maxY);
}

RenderSnapshot Game::createRenderSnapshot(float interpolation) const
{
    interpolation = std::clamp(interpolation, 0.0f, 1.0f);

    const Vec2& previous = previousState_.player.position;
    const Vec2& current = currentState_.player.position;

    RenderSnapshot snapshot;
    snapshot.playerPosition = {
        previous.x * (1.0f - interpolation) + current.x * interpolation,
        previous.y * (1.0f - interpolation) + current.y * interpolation};
    snapshot.playerSize = currentState_.player.size;
    snapshot.score = currentState_.score;
    snapshot.paused = currentState_.paused;

    return snapshot;
}

const GameState& Game::state() const noexcept
{
    return currentState_;
}

} // namespace game
