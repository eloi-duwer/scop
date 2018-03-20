#version 330

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 in_color;
uniform mat4 rotation;
uniform mat4 projection;
uniform vec3 deplacement;

out	vec3 color;

void main()
{
  gl_Position = projection * (rotation * vec4(position, 1.0) + vec4(deplacement, 0));
   color = in_color;
}
