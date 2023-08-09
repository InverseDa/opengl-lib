#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColors;

out vec3 ourColor;

uniform mat4 model;

void main() {
    mat4 m = mat4(1.0f);
    gl_Position = model * vec4(aPos, 1.0);
    ourColor = aColors;
}