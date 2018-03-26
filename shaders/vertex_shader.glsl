#version 330

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 in_color;
uniform mat4 rotation;
uniform mat4 projection;
uniform vec3 deplacement;
uniform vec3 compensation_pos;
uniform float scale;

out		vec2 tex_pos;
void main()
{
	vec3 final_position = (position - compensation_pos) * scale;
	gl_Position = projection * (rotation * vec4(final_position, 1.0) + vec4(deplacement, 0));
	//tex_pos = vec2(position.x, position.y);
	final_position = normalize(final_position);
	float r = sqrt(pow(final_position.x, 2) + pow(final_position.y, 2) + pow(final_position.z, 2));
	tex_pos = vec2(acos(final_position.z / r), atan(final_position.y / final_position.x));
}
