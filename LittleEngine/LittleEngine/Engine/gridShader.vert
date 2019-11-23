#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 gl_Color;


layout (std140) uniform Matrices
{
    mat4 proj;
    mat4 view;
	mat4 model;
} matrices;

out vec3 color;
void main()
{
    gl_Position = matrices.proj*matrices.view*matrices.model*vec4(aPos, 1.0);
	color = gl_Color;
}