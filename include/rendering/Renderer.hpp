#pragma once

#include "rendering/Shader.hpp"

#include <GL/glew.h>

#include <filesystem>
#include <vector>

struct GLFWwindow;

struct Point {
    float x;
    float y;
};

struct Color {
    float r;
    float g;
    float b;
    float a = 1.0f;
};

struct Vertex {
    Point position;
    Point uv;
};

class Renderer {
public:
    Renderer(
        const std::filesystem::path& vertexShader,
        const std::filesystem::path& fragmentShader
    );
    ~Renderer();

    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;

    bool beginFrame(GLFWwindow* window, Color background);
    void endFrame(GLFWwindow* window);

    void drawTriangle(
        Point a, Point b, Point c,
        Color color,
        Shader* shader = nullptr,
        GLuint textureId = 0
    );

    void drawRectangle(
        float x, float y,
        float width, float height,
        Color color,
        Shader* shader = nullptr,
        GLuint textureId = 0
    );

    void drawCircle(
        Point center,
        float radius,
        Color color,
        int segments = 64,
        Shader* shader = nullptr,
        GLuint textureId = 0
    );

private:
    void drawVertices(
        GLenum mode,
        const std::vector<Vertex>& vertices,
        Color color,
        Shader* shader,
        GLuint textureId
    );

    Shader defaultShader_;
    GLuint vao_ = 0;
    GLuint vbo_ = 0;

    float windowWidth_ = 0.0f;
    float windowHeight_ = 0.0f;
};