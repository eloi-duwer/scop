#version 330

layout(location = 0) in vec3 vertex;

uniform mat4 model_view_projection_mat;
uniform bool has_uv_coords;

out vec3 vertexPos;

void main() {
	gl_Position = model_view_projection_mat * vec4(vertex, 1);
	vertexPos = vertex;
}
