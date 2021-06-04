#version 330

layout(location = 0) in vec3 vertex;
layout(location = 1) in vec2 inTexCoord;

uniform mat4 model_view_projection_mat;

out vec3 vertexPos;
out vec2 texCoord;

void main() {
	gl_Position = model_view_projection_mat * vec4(vertex, 1);
	vertexPos = vertex;
	texCoord = inTexCoord; 
}
