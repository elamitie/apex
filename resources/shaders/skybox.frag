#version 330 core
in vec3 Position;
out vec4 FragColor;

uniform samplerCube environmentMap;

void main() {
	FragColor = texture(environmentMap, Position);
}