#version 460 core

out vec4 FragColor;

in vec2 texture_coords_out;

uniform sampler2D texture_sampler;

void main()
{
	FragColor = texture(texture_sampler, texture_coords_out);
}
