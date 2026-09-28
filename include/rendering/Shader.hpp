#pragma once

#include <GL/glew.h>

#include <filesystem>

class Shader {
public:
    Shader(const std::filesystem::path& vertexPath,
           const std::filesystem::path& fragmentPath);
    ~Shader();

    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;

    void use() const;

    void setInt(const char* name, int value) const;
    void setFloat(const char* name, float value) const;
    void setVec2(const char* name, float x, float y) const;
    void setVec4(const char* name, float x, float y, float z, float w) const;

    GLuint id() const { return program_; }

private:
    GLuint program_ = 0;
};