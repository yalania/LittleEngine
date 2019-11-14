#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 glColor;


layout (std140) uniform Matrices
{
    mat4 proj;
    mat4 view;
} matrices;
uniform mat4 model;

out vec3 color;
void main()
{
    gl_Position = matrices.proj*matrices.view*model*vec4(aPos, 1.0);
	color = glColor;
}