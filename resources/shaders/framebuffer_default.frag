#version 330 core
out vec4 color;
in vec2 TexCoords;

uniform sampler2D postProcess_texture;

void main()
{
	color = texture(postProcess_texture, TexCoords);
}