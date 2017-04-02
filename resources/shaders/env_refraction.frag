#version 330 core
out vec4 FragColor;

in vec3 Position;
in vec3 Normal;

uniform vec3 cameraPos;
uniform samplerCube skybox;

const float air = 1.00 / 1.00;
const float water = 1.00 / 1.33;
const float ice = 1.00 / 1.309;
const float glass = 1.00 / 1.52;
const float diamond = 1.00 / 2.42;

void main() {
	// refractive ratio of glass
	float ratio = 1.00 / 1.52;
	vec3 I = normalize(Position - cameraPos);
	vec3 R = refract(I, normalize(Normal), ratio);
	FragColor = texture(skybox, R);
}