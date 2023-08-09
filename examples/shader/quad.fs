#version 330 core
in vec2 TexCoord;
out vec4 FragColor;

uniform sampler2D finalImage;

void main() {
    // FragColor = texture(finalImage, gl_FragCoord.xy / vec2(800, 600));
    FragColor = texture(finalImage, TexCoord);
}