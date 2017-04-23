#version 330 core
out vec4 FragColor;

in VS_OUT {
	vec3 FragPos;
	vec2 TexCoords;
	vec3 TangentLightPos;
	vec3 TangentViewPos;
	vec3 TangentFragPos;
} fs_in;

uniform sampler2D diffuse1;
uniform sampler2D specular1;
uniform sampler2D normal1;
uniform float shininess;

uniform vec3 lightAmbient;
uniform vec3 lightDiffuse;
uniform vec3 lightSpecular;

void main()
{
	vec3 normal = texture(normal1, fs_in.TexCoords).rgb;
	normal = normalize(normal * 2.0 - 1.0);

    // Ambient
    vec3 ambient = lightAmbient * vec3(texture(diffuse1, fs_in.TexCoords));
  	
    // Diffuse 
    vec3 lightDir = normalize(fs_in.TangentLightPos - fs_in.TangentFragPos);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = lightDiffuse * diff * vec3(texture(diffuse1, fs_in.TexCoords));
    
    // Specular
    vec3 viewDir = normalize(fs_in.TangentViewPos - fs_in.TangentFragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
	vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), shininess);
    vec3 specular = lightSpecular * spec * vec3(texture(specular1, fs_in.TexCoords));
        
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
} 