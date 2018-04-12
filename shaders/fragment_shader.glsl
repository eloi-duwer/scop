#version 420

uniform sampler2D tex;
uniform int	color_id;
in vec2 tex_pos;
in vec2 texCord;

out vec3 outputColor;

void main()
{
	outputColor = vec3(texture(tex, texCord).rgb);
	//outputColor = vec3(texture(tex, tex_pos).rgb);
	//outputColor = vec3(texCord, 1.0);
	/*float nb_colors = 11.0;
	float buf_color = (1.0 / nb_colors) * float(color_id % int(nb_colors) + 1);
	outputColor = vec3(buf_color, buf_color, buf_color);*/
}
