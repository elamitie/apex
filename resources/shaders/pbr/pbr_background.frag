#version 330 core
out vec4 FragColor;

in vec3 Position;

uniform samplerCube environmentMap;

void main() {		
	// -- if we want to render the prefilter map ->
    //vec3 envColor = textureLod(environmentMap, Position, 1.2).rgb;
	// ------------------------------------------------------------
	
	// Render the environment map
	vec3 envColor = textureLod(environmentMap, Position, 0.0).rgb;
    
    // HDR tonemap and gamma correct
    envColor = envColor / (envColor + vec3(1.0));
    envColor = pow(envColor, vec3(1.0/2.2)); 
    
    FragColor = vec4(envColor, 1.0);
}