#version 330 core
struct Material
{
	sampler2D diffuse1;
	sampler2D specular1;
	float shininess;
};

struct Light
{
	vec3 position;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

out vec4 color;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;
  
uniform vec3 viewPos;
uniform Light light;
uniform Material material;

void main()
{
    // Ambient
    vec3 ambient = light.ambient * vec3(texture(material.diffuse1, TexCoords));
  	
    // Diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse1, TexCoords));
    
    // Specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.specular1, TexCoords));
        
    vec3 result = ambient + diffuse + specular;
    color = vec4(result, 1.0);
} 