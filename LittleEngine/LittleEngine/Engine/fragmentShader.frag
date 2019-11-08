
#version 330 core
out vec4 FragColor;

in vec3 color;
in vec2 textureCoords;
uniform sampler2D textureImg;

void main()
{
    FragColor = texture(textureImg, textureCoords);
}