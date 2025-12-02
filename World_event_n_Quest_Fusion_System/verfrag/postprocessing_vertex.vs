#version 330 core
layout (location = 0) in vec4 vertex;

out vec2 texCoords;

uniform bool shake;
uniform float time;

void main() {
    gl_Position = vec4(vertex.xy, 1.0, 1.0);
    texCoords = vertex.zw;

    if (shake) {
        float strength = 0.01f;
        gl_Position.x += cos(time * 5) * strength;
        gl_Position.y += cos(time * 7.5) * strength;
    }
}