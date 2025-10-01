#version 330 core
out vec4 color;

in vec2 texCoords;

uniform sampler2D sprite;
uniform vec3 texColor;

void main() {
    //color = vec4(texColor, 1.0) * texture(sprite, texCoords);
    color = vec4(texColor, 1.0);
}