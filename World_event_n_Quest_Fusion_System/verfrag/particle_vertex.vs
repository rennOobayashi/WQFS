#version 330 core
layout (location = 0) in vec4 vertex;

out vec4 particleColor;
out vec2 texCoords;

uniform mat4 projection;
uniform vec4 color;
uniform vec2 offset;
uniform float scale;

void main() {
    texCoords = vertex.zw;
    particleColor = color;
    gl_Position = vec4(offset, 0.0f, 1.0f) * vec4((vertex.xy * scale), 0.0, 1.0);
}