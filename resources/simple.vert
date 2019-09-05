#version 330

layout (location = 0) in vec4 a_position;

//uniform mat4 MVP;

void main(void) {
    gl_Position = a_position;
}
