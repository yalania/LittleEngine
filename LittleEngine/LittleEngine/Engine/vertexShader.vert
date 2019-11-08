#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 vertexColor;
layout (location = 2) in vec2 vertexTexture;


layout (std140) uniform Matrices
{
    mat4 proj;
    mat4 view;
};
uniform mat4 model;

out vec3 color;
out vec2 textureCoords;
void main()
{
    gl_Position = proj*view*model*vec4(aPos, 1.0);
	color = vertexColor;
	textureCoords = vertexTexture;
}