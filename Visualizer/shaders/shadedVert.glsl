#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in float angle;
//layout(location = 2) in vec3 color;

uniform mat4 modelView;
uniform mat4 projection;

out vec3 fragNormal;
out vec3 fragPosition;
out vec3 fragColor;

void main() {
    if ((angle > 60) && (angle < 91))
    {
        fragColor = vec3 (0.0, 1.0, 0.0);
    }
    else
    {
        fragColor = vec3 (1.0, 0.0 ,0.0);
    }
    fragPosition = vec3(modelView * vec4(position, 1.0));
    fragNormal = mat3(transpose(inverse(modelView))) * normal;
    gl_Position = projection * vec4(fragPosition, 1.0);
}