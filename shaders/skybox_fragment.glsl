#version 330

out vec3 color;

in vec3 vertexPos;

uniform samplerCube skyboxSampler;

void main()
{
	color = texture(skyboxSampler, vertexPos).rgb;
}