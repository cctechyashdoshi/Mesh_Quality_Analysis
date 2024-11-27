#version 330 core
layout(location = 0) in vec3 position;
layout(location = 2) in double angle;
//layout(location = 2) in vec3 color;

uniform mat4 modelView;
uniform mat4 projection;

out vec3 fragPosition;
out vec4 fragColor;

void main() 
{
    if ((angle > 44) && (angle < 91))
    {
        vec3 fragColor1 = vec3 (0.0, 1.0, 0.0);
    }
    else
    {
        vec3 fragColor1 = vec3 (1.0, 0.0 ,0.0);
    }
    fragPosition = vec3(modelView * vec4(position, 1.0));
    gl_Position = projection * vec4(fragPosition, 1.0);
    fragColor = vec4(fragColor1,1.0);
}