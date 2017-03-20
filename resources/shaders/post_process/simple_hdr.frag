#version 330 core
out vec4 color;
in vec2 TexCoords;

uniform sampler2D postProcess_texture;

void main()
{
	// reinhard tone mapping (with gamma correction!)
	const float gamma = 2.2;
	vec3 hdrColor = texture(postProcess_texture, TexCoords).rgb;

	vec3 mapped = hdrColor / (hdrColor + vec3(1.0));
	mapped = pow(mapped, vec3(1.0 / gamma));

	color = vec4(mapped, 1.0);
}