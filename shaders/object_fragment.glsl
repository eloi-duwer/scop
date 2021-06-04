#version 330

uniform uint frames;
uniform sampler2D textureSampler;
uniform float display_percent;
uniform vec3 min_coord;
uniform	vec3 max_coord;
uniform bool has_uv_coords;

in vec3 vertexPos;
in vec2 texCoord;

out vec3 color;

vec3 inv_lerp(vec3 value, vec3 minFrom, vec3 maxFrom, vec3 minTo, vec3 maxTo)
{
  return (minTo + (value - minFrom) * (maxTo - minTo) / (maxFrom - minFrom));
}

/*
** Center is where the interpolation returns 1 * color,
** And we do a linear interpolation to center - 1 and center + 1, which must return respectively 0 * color
*/
vec3 interpolate_color_around_center(vec3 color, float center, float current_display_percent)
{
	return (color * (1 - abs(current_display_percent - center)));
}

/*
** Linear interpolation optimized, to convert from -1 / 1 to 0 / 1
*/
float to_color_range(float color)
{
	return (color + 1) / 2;
}

/*
** Renders between 2 and 4
*/
vec3 get_rainbow_oscilating_color()
{
	if (display_percent < 2 || display_percent > 4)
		return vec3(0, 0, 0);

	return interpolate_color_around_center(
		vec3(
			0.9 * to_color_range(cos(frames / 53.0f)),
			0.9 * to_color_range(-cos(frames / 79.0f)),
			0.9 * to_color_range(-cos(frames / 71.0f))
		),
		3,
		display_percent
	);
}

/*
** Renders between 3 and 1, centered at 0
*/
vec3 get_automatic_face_color_gray()
{
	if (display_percent > 1 && display_percent < 3)
		return vec3(0, 0, 0);

	const int nb_faces_with_same_color = 1;
	const int nb_different_colors = 10;
	float col = 1.0 - ((gl_PrimitiveID / nb_faces_with_same_color) % nb_different_colors) / (nb_different_colors - 1.0);
	return interpolate_color_around_center(
		vec3(col, col, col),
		0,
		display_percent - (4 * int(display_percent > 1))
	);
}

//Renders between 0 and 2
vec3 get_texture_color()
{
	if (display_percent > 2)
		return vec3(0, 0, 0);

	vec2 uvPos;
	if (has_uv_coords)
		uvPos = texCoord;
	else
		uvPos = vertexPos.yz;
	return interpolate_color_around_center(
		texture(textureSampler, uvPos).rgb,
		1,
		display_percent
	);
}

//Renders between 1 and 3
vec3 get_color_gradient()
{
	if (display_percent < 1 || display_percent > 3)
		return vec3 (0, 0, 0);

	return interpolate_color_around_center(
		inv_lerp(vertexPos, min_coord, max_coord, vec3(0.2, 0.2, 0.2), vec3(1, 1, 1)),
		2,
		display_percent
	);
}

void main()
{
	color = get_color_gradient()
		+ get_texture_color()
		+ get_automatic_face_color_gray()
		+ get_rainbow_oscilating_color();
}
