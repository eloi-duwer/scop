#version 330
layout (location = 0) in vec3 vertex;

out vec3 vertexPos;

uniform mat4 view_projection_mat;

void main()
{
	vertexPos = vertex;
	gl_Position = (view_projection_mat * vec4(vertex, 1)).xyww;
}