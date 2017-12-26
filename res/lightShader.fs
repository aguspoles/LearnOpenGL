#version 330 core

struct Material{
       vec3 ambient;
       vec3 diffuse;
       vec3 specular;
       float shininess;
};
struct Light{
       vec3 position;
       vec3 ambient;
       vec3 diffuse;
       vec3 specular;
};


in vec2 texCoord0;
in vec3 normal0;
in vec3 FragPos;

out vec4 FragColor;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform sampler2D texture_normal1;

uniform Material material;
uniform Light light;
uniform vec3 viewPos;

void main()
{
        vec3 norm = normalize(normal0);
        vec3 lightDir = normalize(light.position - FragPos);

//specular
        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
        vec3 specular = light.specular * spec * material.specular;

//diffuse
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = diff * material.diffuse * light.diffuse;

//ambient
        vec3 ambientLight = material.ambient * light.ambient;

        vec4 t0 = texture(texture_diffuse1, texCoord0);
        vec4 t1 = texture(texture_specular1, texCoord0);
        vec4 t2 = texture(texture_normal1, texCoord0);

        vec3 result = (ambientLight + diffuse + specular) * t0 * t1 * t2 * 5;
	
        FragColor = vec4(result, 1.0);
}
