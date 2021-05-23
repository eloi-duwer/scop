#version 330

#define M_PI 3.141592653589793

layout(location = 0) in vec3 vertex;

uniform mat4 model_view_projection_mat;
uniform vec3 center;
uniform bool has_uv_coords;

out	vec2 uv_coords;

/*
	Extrapolation automatique des coordonnées uv, a partir des coordonnées du point
	Basé sur https://people.cs.clemson.edu/~dhouse/courses/405/notes/texture-maps.pdf
	Utilisé pour mapper les points d'une sphere
	Marche pas trop mal pour tout les objets
*/
void automatic_uv_calc()
{
	/*vec3 centered_pos = vertex - center;
	
	float angle1 = atan(-(centered_pos.z), centered_pos.x);
	float angle2 = acos(-(centered_pos.y) / distance(center, vertex));

	uv_coords = vec2((angle1 + M_PI) / (2 * M_PI), angle2 / M_PI);*/

	uv_coords = vec2(vertex.y, vertex.z);
}

void main() {
	gl_Position = model_view_projection_mat * vec4(vertex, 1);

	if (!has_uv_coords)
		automatic_uv_calc();
}
