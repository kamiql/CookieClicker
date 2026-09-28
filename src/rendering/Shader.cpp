#include "rendering/Shader.hpp"

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>

namespace {

std::string readFile(const std::filesystem::path& path) {
    std::ifstream file(path);

    if (!file) {
        throw std::runtime_error(
            "Shader-Datei nicht gefunden: " + path.string()
        );
    }

    std::ostringstream contents;
    contents << file.rdbuf();
    return contents.str();
}

GLuint compileShader(
    GLenum type,
    const std::string& source,
    const std::filesystem::path& path
) {
    const GLuint shader = glCreateShader(type);
    if (shader == 0) {
        throw std::runtime_error(
            "Shader konnte nicht erstellt werden: " + path.string()
        );
    }

    const char* sourcePtr = source.c_str();
    glShaderSource(shader, 1, &sourcePtr, nullptr);
    glCompileShader(shader);

    GLint success = GL_FALSE;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (success != GL_TRUE) {
        GLint logLength = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);

        std::string log(static_cast<std::size_t>(logLength), '\0');
        glGetShaderInfoLog(shader, logLength, nullptr, log.data());

        glDeleteShader(shader);

        throw std::runtime_error(
            "Shader-Kompilierung fehlgeschlagen (" +
            path.string() + "):\n" + log
        );
    }

    return shader;
}

} // namespace

Shader::Shader(
    const std::filesystem::path& vertexPath,
    const std::filesystem::path& fragmentPath
) {
    const std::string vertexSource = readFile(vertexPath);
    const std::string fragmentSource = readFile(fragmentPath);

    GLuint vertex = 0;
    GLuint fragment = 0;

    try {
        vertex = compileShader(
            GL_VERTEX_SHADER, vertexSource, vertexPath
        );
        fragment = compileShader(
            GL_FRAGMENT_SHADER, fragmentSource, fragmentPath
        );

        program_ = glCreateProgram();
        if (program_ == 0) {
            throw std::runtime_error(
                "Shader-Programm konnte nicht erstellt werden."
            );
        }

        glAttachShader(program_, vertex);
        glAttachShader(program_, fragment);
        glLinkProgram(program_);

        GLint success = GL_FALSE;
        glGetProgramiv(program_, GL_LINK_STATUS, &success);

        if (success != GL_TRUE) {
            GLint logLength = 0;
            glGetProgramiv(program_, GL_INFO_LOG_LENGTH, &logLength);

            std::string log(static_cast<std::size_t>(logLength), '\0');
            glGetProgramInfoLog(
                program_, logLength, nullptr, log.data()
            );

            throw std::runtime_error(
                "Shader-Linking fehlgeschlagen:\n" + log
            );
        }

        glDeleteShader(vertex);
        glDeleteShader(fragment);
    } catch (...) {
        if (vertex) glDeleteShader(vertex);
        if (fragment) glDeleteShader(fragment);
        if (program_) glDeleteProgram(program_);

        program_ = 0;
        throw;
    }
}

Shader::~Shader() {
    if (program_) {
        glDeleteProgram(program_);
    }
}

void Shader::use() const {
    glUseProgram(program_);
}

void Shader::setInt(const char* name, int value) const {
    glUniform1i(glGetUniformLocation(program_, name), value);
}

void Shader::setFloat(const char* name, float value) const {
    glUniform1f(glGetUniformLocation(program_, name), value);
}

void Shader::setVec2(const char* name, float x, float y) const {
    glUniform2f(glGetUniformLocation(program_, name), x, y);
}

void Shader::setVec4(
    const char* name, float x, float y, float z, float w
) const {
    glUniform4f(
        glGetUniformLocation(program_, name),
        x, y, z, w
    );
}