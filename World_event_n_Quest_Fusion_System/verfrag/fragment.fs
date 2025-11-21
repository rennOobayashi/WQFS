#version 330 core
out vec4 color;

in vec2 texCoords;

uniform sampler2D sprite;
uniform vec4 texColor;
uniform bool isSprite;

void main() {
    if (isSprite) {
        color = vec4(texColor) * texture(sprite, texCoords);
    }
    else {
        color = vec4(texColor);
    }
}