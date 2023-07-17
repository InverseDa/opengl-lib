#version 330 core
in vec3 fragment;
out vec4 fcolor;

void main() {
    fcolor = vec4(fragment, 1.0);
}