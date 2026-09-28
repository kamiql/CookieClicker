#version 330 core

layout(location = 0) in vec2 aPosition;
layout(location = 1) in vec2 aUV;

out vec2 vUV;

void main() {
    vec2 clipPosition = vec2(
            aPosition.x * 2.0 - 1.0,
            1.0 - aPosition.y * 2.0
    );

    gl_Position = vec4(clipPosition, 0.0, 1.0);
    vUV = aUV;
}