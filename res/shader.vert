#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec3 normal; // Neue Zeile für Normalen

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 fragColor;
out vec3 fragNormal; // Neue Zeile für Normalen
out vec3 fragPos; // Neue Zeile für Fragmentposition

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0);
    fragColor = color;
    fragNormal = mat3(transpose(inverse(model))) * normal; // Transformierte Normalen
    fragPos = vec3(model * vec4(position, 1.0)); // Berechnete Fragmentposition
}