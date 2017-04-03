#version 330 core
layout (location = 0) in vec3 position;

out vec3 World;

uniform mat4 projection;
uniform mat4 view;

void main() {
	World = position;
	gl_Position = projection * view * vec4(World, 1.0);
}