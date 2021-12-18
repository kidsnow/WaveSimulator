#version 330

layout (location = 0) out vec4 finalColor;

in vec3 vertexColor;

void main(void) {
    finalColor = vec4(vertexColor, 1.0);
}
