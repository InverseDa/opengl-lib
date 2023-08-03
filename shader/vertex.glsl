#version 330 core
layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 color;
layout(location = 2) in vec2 texCoord;

out vec3 fragment;

uniform mat4 projection;
uniform mat4 model;
uniform mat4 view;

void main() {
    gl_Position = projection * view * model * vec4(pos, 1.0f);
    // gl_Position = vec4(pos, 1.0f);
    fragment = color;
}