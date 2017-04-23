#version 330 core
in vec3 Normal;
in vec3 Position;
in vec2 TexCoords;

uniform vec3 cameraPos;
uniform sampler2D diffuse1;
uniform sampler2D reflection1;
uniform samplerCube skybox;

out vec4 color;

void main()
{             
    // Diffuse
    vec4 diffuseColor = texture(diffuse1, TexCoords);
    // Reflection
    vec3 I = normalize(Position - cameraPos);
    vec3 R = reflect(I, normalize(Normal));
    float reflectIntensity = texture(reflection1, TexCoords).r;
    vec4 reflectColor;
    if(reflectIntensity > 0.1) // Only sample reflections when above a certain treshold
        reflectColor = texture(skybox, R) * reflectIntensity;
    // Combine them
    color = diffuseColor + reflectColor;
}