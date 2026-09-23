# Simple2DTickRender

Minimal SDL3/C++17 project with:

- a fixed-rate game simulation (`Game::tick`),
- variable-rate rendering,
- optional maximum render FPS as an upper bound,
- input events delivered once to the next game tick,
- interpolation between the previous and current game state.

## Build

Install SDL3 with its CMake package, then:

```bash
cmake -S . -B build
cmake --build build
./build/simple2d
```

On Windows, run `build/Debug/simple2d.exe` or `build/Release/simple2d.exe` depending on the generator.

## Runtime behaviour

- Game simulation: 60 ticks per second.
- Rendering: as fast as possible by default.
- To cap rendering, pass a maximum FPS to `Application`, or change the value in `src/app/Application.cpp`.
- The limiter never forces the application to reach the configured FPS. If rendering is slower, the achieved FPS is lower.

The example moves a square with **A/D** or **Left/Right** and toggles pause with **P**.
