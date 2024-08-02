#version 330 core
in vec3 fragColor;
in vec3 fragNormal;
in vec3 fragPos;
in vec2 fragTexCoords; 

out vec4 color;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 lightColor;
uniform vec3 emission;
uniform sampler2D texture1; 

void main()
{
    // Ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    // Diffuse
    vec3 norm = normalize(fragNormal);
    vec3 lightDir = normalize(lightPos - fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // Specular
    float specularStrength = 1.;
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;

    // Texturfarbe
    vec3 textureColor = texture(texture1, fragTexCoords).rgb;

    vec3 result = (ambient + diffuse + specular + emission) * textureColor;
    color = vec4(result, 1.0);
}
