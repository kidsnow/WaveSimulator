#version 330

layout (location = 0) in vec3 a_position;
layout (location = 1) in vec3 a_color;

out vec3 vertexColor;

uniform bool hasColor;
uniform vec3 color;
uniform mat4 viewProjection;

void main(void) {
    if (hasColor)
        vertexColor = color;
    else
        vertexColor = a_color;

    gl_Position = viewProjection * vec4(a_position, 1.0);
}
