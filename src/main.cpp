#include "config.h"
#include "game/GameScene.hpp"
#include "game/SaveManager.hpp"
#include "rendering/Renderer.hpp"

#include "rendering/Shader.hpp"

using namespace std;

int main() {
    if (!glfwInit()) {
        cerr << "Failed to initialize GLFW3" << endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(
        1280, 720, "Cookie Clicker", nullptr, nullptr
    );

    if (!window) {
        cerr << "Failed to create Window" << endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        cerr << "Failed to initialize GLEW" << endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    glGetError();

    int exitCode = 0;

    try {
        Renderer renderer(
            std::filesystem::path(SHADER_DIR) / "basic.vert",
            std::filesystem::path(SHADER_DIR) / "basic.frag"
        );
        GameScene scene;

        SaveData save = SaveManager::load(savePath);

        double lastFrameTime = glfwGetTime();
        double timeSinceSave = 0.0;

        while (!glfwWindowShouldClose(window)) {
            const double currentTime = glfwGetTime();
            const double deltaTime = currentTime - lastFrameTime;
            lastFrameTime = currentTime;

            glfwPollEvents();
            scene.update(window, &save);

            if (renderer.beginFrame(window, {0.5f, 0.5f, 0.5f})) {
                scene.render(renderer);
                renderer.endFrame(window);
            }

            timeSinceSave += deltaTime;

            if (timeSinceSave >= 30.0) {
                SaveManager::save(savePath, save);
                timeSinceSave = 0.0;

                cout << "Saved game" << endl;
            }
        }
    } catch (const std::exception &error) {
        std::cerr << error.what() << '\n';
        exitCode = 1;
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return exitCode;
}
