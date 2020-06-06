#version 330

uniform uint frames;
uniform sampler2D textureSampler;
uniform float display_percent;

in vec2 uv_coords;

out vec3 color;

float to_color_range(float color)
{
	return (color + 1) / 2;
}

vec3 get_rainbow_color()
{
	return vec3(
		to_color_range(cos(frames / 50.0f)),
		to_color_range(-cos(frames / 50.0f)),
		to_color_range(-cos(frames / 37.5f))
	);
}


const int nb_faces_with_same_color = 1;
const int nb_different_colors = 10;

float get_automatic_face_color_grey()
{
	return 1 - ((gl_PrimitiveID / nb_faces_with_same_color) % nb_different_colors) / (nb_different_colors - 1.0f);
}

vec3 get_texture_color()
{
	return texture(textureSampler, uv_coords).rgb;
}

void main() {

	//color = get_rainbow_color() * get_automatic_face_color_grey();
	if (display_percent <= 0)
		color = vec3(get_automatic_face_color_grey());
	else if (display_percent >= 1)
		color = get_texture_color();
	else {
		color = vec3(get_automatic_face_color_grey()) * (1 - display_percent) + get_texture_color() * display_percent;
	}
}
