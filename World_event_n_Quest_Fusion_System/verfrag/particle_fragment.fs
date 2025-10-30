#version 330 core
out vec4 color;

in vec4 particleColor;
in vec2 texCoords;

uniform sampler2D sprite;

void main() {
    color = vec4(texture(sprite, texCoords) * particleColor);
}