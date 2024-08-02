#version 330 core
in vec3 fragColor;
in vec3 fragNormal; // Neue Zeile für Normalen
in vec3 fragPos; // Neue Zeile für Fragmentposition

out vec4 color;

uniform vec3 lightPos; // Position des Lichts
uniform vec3 viewPos; // Position der Kamera
uniform vec3 lightColor; // Farbe des Lichts
uniform vec3 objColor; // Farbe des Objekts
uniform vec3 emission;

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
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;

    vec3 result = (ambient + diffuse + specular + emission) * objColor;
    color = vec4(result, 1.0);
}
