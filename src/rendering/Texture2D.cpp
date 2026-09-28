#include "rendering/Texture2D.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <stdexcept>
#include <string>

Texture2D::Texture2D(
    const std::filesystem::path& imagePath
) {
    int width = 0;
    int height = 0;
    int channels = 0;

    const std::string filename = imagePath.string();

    stbi_set_flip_vertically_on_load(0);

    unsigned char* pixels = stbi_load(
        filename.c_str(),
        &width,
        &height,
        &channels,
        STBI_rgb_alpha
    );

    if (!pixels) {
        const char* reason = stbi_failure_reason();

        throw std::runtime_error(
            "Bild konnte nicht geladen werden: " +
            filename + " (" +
            (reason ? reason : "unbekannter Fehler") + ")"
        );
    }

    glGenTextures(1, &textureId_);

    if (textureId_ == 0) {
        stbi_image_free(pixels);
        throw std::runtime_error(
            "OpenGL-Textur konnte nicht erstellt werden."
        );
    }

    glBindTexture(GL_TEXTURE_2D, textureId_);

    glTexParameteri(
        GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE
    );
    glTexParameteri(
        GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE
    );
    glTexParameteri(
        GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR
    );
    glTexParameteri(
        GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR
    );

    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGBA,
        width,
        height,
        0,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        pixels
    );

    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(pixels);
}

Texture2D::~Texture2D() {
    if (textureId_) {
        glDeleteTextures(1, &textureId_);
    }
}