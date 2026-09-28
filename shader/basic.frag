#version 330 core

in vec2 vUV;

uniform vec4 uColor;
uniform sampler2D uTexture;
uniform int uHasTexture;

out vec4 fragColor;

void main() {
    vec4 texColor = vec4(1.0);

    if (uHasTexture != 0) {
        texColor = texture(uTexture, vUV);
    }

    fragColor = uColor * texColor;
}