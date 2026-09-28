#include "rendering/Renderer.hpp"

#include <GLFW/glfw3.h>

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <stdexcept>

namespace {

constexpr float pi = 3.14159265358979323846f;

}

Renderer::Renderer(
    const std::filesystem::path& vertexShader,
    const std::filesystem::path& fragmentShader
)
    : defaultShader_(vertexShader, fragmentShader) {

    glGenVertexArrays(1, &vao_);
    glGenBuffers(1, &vbo_);

    if (vao_ == 0 || vbo_ == 0) {
        if (vbo_) glDeleteBuffers(1, &vbo_);
        if (vao_) glDeleteVertexArrays(1, &vao_);

        throw std::runtime_error(
            "VAO oder VBO konnte nicht erstellt werden."
        );
    }

    glBindVertexArray(vao_);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);

    glVertexAttribPointer(
        0, 2, GL_FLOAT, GL_FALSE,
        sizeof(Vertex),
        reinterpret_cast<void*>(offsetof(Vertex, position))
    );
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(
        1, 2, GL_FLOAT, GL_FALSE,
        sizeof(Vertex),
        reinterpret_cast<void*>(offsetof(Vertex, uv))
    );
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Renderer::~Renderer() {
    if (vbo_) glDeleteBuffers(1, &vbo_);
    if (vao_) glDeleteVertexArrays(1, &vao_);
}

bool Renderer::beginFrame(
    GLFWwindow* window,
    Color background
) {
    int windowWidth = 0;
    int windowHeight = 0;
    int framebufferWidth = 0;
    int framebufferHeight = 0;

    glfwGetWindowSize(
        window, &windowWidth, &windowHeight
    );
    glfwGetFramebufferSize(
        window, &framebufferWidth, &framebufferHeight
    );

    if (windowWidth <= 0 || windowHeight <= 0 ||
        framebufferWidth <= 0 || framebufferHeight <= 0) {
        windowWidth_ = 0.0f;
        windowHeight_ = 0.0f;
        return false;
    }

    windowWidth_ = static_cast<float>(windowWidth);
    windowHeight_ = static_cast<float>(windowHeight);

    glViewport(0, 0, framebufferWidth, framebufferHeight);

    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glClearColor(
        background.r,
        background.g,
        background.b,
        background.a
    );
    glClear(GL_COLOR_BUFFER_BIT);

    return true;
}

void Renderer::endFrame(GLFWwindow* window) {
    glfwSwapBuffers(window);
}

void Renderer::drawVertices(
    GLenum mode,
    const std::vector<Vertex>& vertices,
    Color color,
    Shader* shader,
    GLuint textureId
) {
    if (vertices.empty() ||
        windowWidth_ <= 0.0f ||
        windowHeight_ <= 0.0f) {
        return;
    }

    Shader& activeShader =
        shader != nullptr ? *shader : defaultShader_;

    activeShader.use();

    activeShader.setVec4(
        "uColor",
        color.r, color.g, color.b, color.a
    );
    activeShader.setVec2(
        "uWindowSize",
        windowWidth_, windowHeight_
    );
    activeShader.setInt(
        "uHasTexture",
        textureId != 0 ? 1 : 0
    );
    activeShader.setInt("uTexture", 0);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureId);

    glBindVertexArray(vao_);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);

    glBufferData(
        GL_ARRAY_BUFFER,
        static_cast<GLsizeiptr>(
            vertices.size() * sizeof(Vertex)
        ),
        vertices.data(),
        GL_DYNAMIC_DRAW
    );

    glDrawArrays(
        mode,
        0,
        static_cast<GLsizei>(vertices.size())
    );

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Renderer::drawTriangle(
    Point a, Point b, Point c,
    Color color,
    Shader* shader,
    GLuint textureId
) {
    drawVertices(
        GL_TRIANGLES,
        {
            {a, {0.0f, 0.0f}},
            {b, {1.0f, 0.0f}},
            {c, {0.0f, 1.0f}}
        },
        color,
        shader,
        textureId
    );
}

void Renderer::drawRectangle(
    float x, float y,
    float width, float height,
    Color color,
    Shader* shader,
    GLuint textureId
) {
    if (width <= 0.0f || height <= 0.0f) {
        return;
    }

    drawVertices(
        GL_TRIANGLES,
        {
            {{x,         y},          {0.0f, 0.0f}},
            {{x + width, y},          {1.0f, 0.0f}},
            {{x + width, y + height}, {1.0f, 1.0f}},

            {{x,         y},          {0.0f, 0.0f}},
            {{x + width, y + height}, {1.0f, 1.0f}},
            {{x,         y + height}, {0.0f, 1.0f}}
        },
        color,
        shader,
        textureId
    );
}

void Renderer::drawCircle(
    Point center,
    float radius,
    Color color,
    int segments,
    Shader* shader,
    GLuint textureId
) {
    if (radius <= 0.0f ||
        windowWidth_ <= 0.0f ||
        windowHeight_ <= 0.0f) {
        return;
    }

    segments = std::clamp(segments, 3, 512);

    const float radiusX =
        radius * windowHeight_ / windowWidth_;

    std::vector<Vertex> vertices;
    vertices.reserve(
        static_cast<std::size_t>(segments) + 2
    );

    vertices.push_back({
        center,
        {0.5f, 0.5f}
    });

    for (int i = 0; i <= segments; ++i) {
        const float angle =
            2.0f * pi * static_cast<float>(i) /
            static_cast<float>(segments);

        const float c = std::cos(angle);
        const float s = std::sin(angle);

        vertices.push_back({
            {
                center.x + c * radiusX,
                center.y + s * radius
            },
            {
                0.5f + c * 0.5f,
                0.5f + s * 0.5f
            }
        });
    }

    drawVertices(
        GL_TRIANGLE_FAN,
        vertices,
        color,
        shader,
        textureId
    );
}