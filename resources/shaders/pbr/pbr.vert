#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoords;
layout (location = 2) in vec3 normal;

out vec3 Position;
out vec2 TexCoords;
out vec3 Normal;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main() {
	TexCoords = texCoords;
	Position = vec3(model * vec4(pos, 1.0));
	Normal = mat3(normal) * normal;
	
	gl_Position = projection * view * vec4(Position, 1.0);
}