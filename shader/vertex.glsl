#version 330 core
(location = 1) in vec3 pos;

void main() {
    gl_Position = vec4(pos, 1.0f);
}