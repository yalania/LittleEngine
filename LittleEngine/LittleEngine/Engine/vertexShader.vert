#version 330 core
layout (location = 0) in vec3 aPos;


uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;

out vec4 color;
void main()
{
    gl_Position = view*model*vec4(aPos, 1.0);
	color = vec4(1.0,0.5,1.0,1.0);
}