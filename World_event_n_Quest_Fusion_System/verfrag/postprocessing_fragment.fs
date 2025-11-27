#version 330 core
out vec4 color;

in vec2 texCoords;

uniform sampler2D scene;
uniform vec2 offsets[9];
uniform int edgeKernel[9];
uniform float blurKernel[9];
uniform bool shake;

void main() {
    color = vec4(0.0);
    vec3 smaple[9];

    if (shake) {
        for (int i = 0; i < 9; ++i) {
            sample[i] = vec3(texture(scene, texCoords.st + offsets[i]));
        }

        for (int i = 0; i < 9; ++i) {
            color += vec4(sample[i] * blurKernel[i], 0.0);
        }
        color.a = 1.0;
    }
    else {
        color = texture(scene, texCoords);
    }
}