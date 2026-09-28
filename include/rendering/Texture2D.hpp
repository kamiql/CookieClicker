#pragma once

#include <GL/glew.h>

#include <filesystem>

class Texture2D {
public:
    explicit Texture2D(
        const std::filesystem::path& imagePath
    );
    ~Texture2D();

    Texture2D(const Texture2D&) = delete;
    Texture2D& operator=(const Texture2D&) = delete;

    GLuint id() const { return textureId_; }

private:
    GLuint textureId_ = 0;
};