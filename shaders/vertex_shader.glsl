#version 330

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 in_color;

out	vec3 color;

void main()
{
    gl_Position = position;
    color = in_color;
}
