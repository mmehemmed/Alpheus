#version 460 core

layout (location = 0) in vec3 position;
layout (location = 0) in vec2 texture_coords;

out vec2 texture_coords_out;

void main()
{
	gl_Position = vec4(position, 1.0);
	texture_coords_out = texture_coords;
}