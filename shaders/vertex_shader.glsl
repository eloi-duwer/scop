#version 330

layout(location = 0) in vec3 vertex;

uniform mat4 model_view_projection_mat;
uniform vec3 center;
uniform bool has_uv_coords;

out	vec2 uv_coords;
out vec3 vertexPos;

//Application plate de la texture sur l'axe y et z, par défaut ca marche...
void automatic_uv_calc()
{
	uv_coords = vec2(vertex.y, vertex.z);
}

void main() {
	gl_Position = model_view_projection_mat * vec4(vertex, 1);
	vertexPos = vertex;

	if (!has_uv_coords)
		automatic_uv_calc();
}
